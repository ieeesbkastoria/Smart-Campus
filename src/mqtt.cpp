#include "../include/mqtt.h"

// Initialize static member
MqttHandler *MqttHandler::_instance = nullptr;

MqttHandler::MqttHandler(const String &clientId, const String &brokerIp,
                         uint16_t brokerPort, const String &username,
                         const String &password)
    : _clientId(clientId), _brokerIp(brokerIp), _brokerPort(brokerPort),
      _username(username), _password(password), _mqttClient(_wifiClient) {

  // Set static instance pointer for callback handling
  _instance = this;

  // Set the broker address and port
  _mqttClient.setServer(_brokerIp.c_str(), _brokerPort);

  // Set the callback for incoming messages
  _mqttClient.setCallback(_onMessageReceived);
}

bool MqttHandler::begin() {
  // Try to connect to the MQTT broker
  return _reconnect();
}

void MqttHandler::loop() {
  // Check if connected to MQTT broker
  if (!_mqttClient.connected()) {
    // Try to reconnect if a certain time has passed since last attempt
    unsigned long currentMillis = millis();
    if (currentMillis - _lastReconnectAttempt > _reconnectInterval) {
      _lastReconnectAttempt = currentMillis;
      if (_reconnect()) {
        // Reset the counter if reconnection was successful
        _lastReconnectAttempt = 0;
      }
    }
  }

  // Process incoming messages
  _mqttClient.loop();
}

bool MqttHandler::publish(const String &topic, const String &message,
                          bool retain) {
  if (!_mqttClient.connected()) {
    return false;
  }

  return _mqttClient.publish(topic.c_str(), message.c_str(), retain);
}

bool MqttHandler::subscribe(const String &topic, MessageCallback callback) {
  // Store the callback
  _topicCallbacks[topic] = callback;

  // Subscribe to the topic if connected
  if (_mqttClient.connected()) {
    return _mqttClient.subscribe(topic.c_str());
  }

  // Will be subscribed on next reconnect
  return true;
}

bool MqttHandler::unsubscribe(const String &topic) {
  // Remove the callback
  _topicCallbacks.erase(topic);

  // Unsubscribe from the topic if connected
  if (_mqttClient.connected()) {
    return _mqttClient.unsubscribe(topic.c_str());
  }

  return true;
}

bool MqttHandler::isConnected() const { return _mqttClient.connected(); }

void MqttHandler::disconnect() { _mqttClient.disconnect(); }

void MqttHandler::setOnConnectCallback(std::function<void()> callback) {
  _onConnectCallback = callback;
}

void MqttHandler::setWill(const String &topic, const String &message,
                          bool retain) {
  _mqttClient.setWill(topic.c_str(), message.c_str(), retain, 1);
}

void MqttHandler::setKeepAlive(uint16_t seconds) {
  _mqttClient.setKeepAlive(seconds);
}

void MqttHandler::setTimeout(uint16_t seconds) {
  _mqttClient.setSocketTimeout(seconds);
}

bool MqttHandler::_reconnect() {
  // Attempt to connect to MQTT broker
  bool connected = false;

  if (_username.length() > 0) {
    connected = _mqttClient.connect(_clientId.c_str(), _username.c_str(),
                                    _password.c_str());
  } else {
    connected = _mqttClient.connect(_clientId.c_str());
  }

  if (connected) {
    Serial.println("Connected to MQTT broker");

    // Resubscribe to all topics
    _resubscribe();

    // Call the connect callback if it exists
    if (_onConnectCallback) {
      _onConnectCallback();
    }
  } else {
    Serial.print("Failed to connect to MQTT broker, rc=");
    Serial.println(_mqttClient.state());
  }

  return connected;
}

void MqttHandler::_resubscribe() {
  // Resubscribe to all topics
  for (const auto &topic : _topicCallbacks) {
    _mqttClient.subscribe(topic.first.c_str());
  }
}

void MqttHandler::_onMessageReceived(char *topic, byte *payload,
                                     unsigned int length) {
  // Create a string from the payload
  String message;
  message.reserve(length);
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  // Forward to the instance method
  if (_instance) {
    _instance->_processMessage(String(topic), message);
  }
}

void MqttHandler::_processMessage(const String &topic, const String &message) {
  // Find the callback for this topic
  auto it = _topicCallbacks.find(topic);
  if (it != _topicCallbacks.end()) {
    // Call the callback with the topic and message
    it->second(topic, message);
  }

  // Check for wildcard subscriptions (simple + and # handling)
  for (const auto &subscription : _topicCallbacks) {
    const String &subTopic = subscription.first;

    // Skip exact matches (already handled)
    if (subTopic == topic) {
      continue;
    }

    // Check if this is a wildcard subscription that matches the topic
    if (subTopic.endsWith("#")) {
      // # wildcard - matches everything after the prefix
      String prefix = subTopic.substring(0, subTopic.length() - 1);
      if (topic.startsWith(prefix)) {
        subscription.second(topic, message);
      }
    } else if (subTopic.indexOf('+') >= 0) {
      // + wildcard - matches a single level
      // Split the subscription and topic into segments
      String subSegments[10]; // Max 10 segments
      String topicSegments[10];
      int subCount = 0;
      int topicCount = 0;

      // Split subscription
      int start = 0;
      int end = subTopic.indexOf('/');
      while (end >= 0 && subCount < 10) {
        subSegments[subCount++] = subTopic.substring(start, end);
        start = end + 1;
        end = subTopic.indexOf('/', start);
      }
      if (start < subTopic.length() && subCount < 10) {
        subSegments[subCount++] = subTopic.substring(start);
      }

      // Split topic
      start = 0;
      end = topic.indexOf('/');
      while (end >= 0 && topicCount < 10) {
        topicSegments[topicCount++] = topic.substring(start, end);
        start = end + 1;
        end = topic.indexOf('/', start);
      }
      if (start < topic.length() && topicCount < 10) {
        topicSegments[topicCount++] = topic.substring(start);
      }

      // Check if they match
      if (subCount == topicCount) {
        bool matches = true;
        for (int i = 0; i < subCount; i++) {
          if (subSegments[i] != "+" && subSegments[i] != topicSegments[i]) {
            matches = false;
            break;
          }
        }

        if (matches) {
          subscription.second(topic, message);
        }
      }
    }
  }
}
