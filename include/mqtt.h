#ifndef MQTT_H_
#define MQTT_H_

#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <functional>
#include <map>
#include <string>

/**
 * @brief A class to handle MQTT connections and messaging for ESP32
 *
 * This class provides a wrapper around PubSubClient to make it easier to
 * use MQTT on ESP32 devices. It handles connection management, automatic
 * reconnection, subscribing to topics, and message callbacks.
 */
class MqttHandler {
public:
  using MessageCallback = std::function<void(const String &, const String &)>;

  /**
   * @brief Construct a new MqttHandler object
   *
   * @param clientId Unique identifier for this MQTT client
   * @param brokerIp IP address of the MQTT broker
   * @param brokerPort Port of the MQTT broker (default: 1883)
   * @param username MQTT broker username (optional)
   * @param password MQTT broker password (optional)
   */
  MqttHandler(const String &clientId, const String &brokerIp,
              uint16_t brokerPort = 1883, const String &username = "",
              const String &password = "");

  /**
   * @brief Initialize and connect to the MQTT broker
   *
   * @return true if connection was successful
   * @return false if connection failed
   */
  bool begin();

  /**
   * @brief Update the MQTT client connection and handle incoming messages
   *
   * Call this method regularly in the main loop
   */
  void loop();

  /**
   * @brief Publish a message to an MQTT topic
   *
   * @param topic The topic to publish to
   * @param message The message to publish
   * @param retain Whether to retain the message (default: false)
   * @return true if publish was successful
   * @return false if publish failed
   */
  bool publish(const String &topic, const String &message, bool retain = false);

  /**
   * @brief Subscribe to an MQTT topic
   *
   * @param topic The topic to subscribe to
   * @param callback Function to call when a message is received on this topic
   * @return true if subscription was successful
   * @return false if subscription failed
   */
  bool subscribe(const String &topic, MessageCallback callback);

  /**
   * @brief Unsubscribe from an MQTT topic
   *
   * @param topic The topic to unsubscribe from
   * @return true if unsubscription was successful
   * @return false if unsubscription failed
   */
  bool unsubscribe(const String &topic);

  /**
   * @brief Check if the client is connected to the MQTT broker
   *
   * @return true if connected
   * @return false if not connected
   */
  bool isConnected() const;

  /**
   * @brief Disconnect from the MQTT broker
   */
  void disconnect();

  /**
   * @brief Set a callback for when connection to the broker is established
   *
   * @param callback Function to call when connected
   */
  void setOnConnectCallback(std::function<void()> callback);

  /**
   * @brief Set the Last Will and Testament message
   *
   * @param topic The topic for the LWT message
   * @param message The LWT message content
   * @param retain Whether to retain the LWT message
   */
  void setWill(const String &topic, const String &message, bool retain = false);

  /**
   * @brief Set the maximum time between sending MQTT keepalives
   *
   * @param seconds Time in seconds (default: 15)
   */
  void setKeepAlive(uint16_t seconds = 15);

  /**
   * @brief Set connection timeout
   *
   * @param seconds Time in seconds (default: 15)
   */
  void setTimeout(uint16_t seconds = 15);

private:
  String _clientId;
  String _brokerIp;
  uint16_t _brokerPort;
  String _username;
  String _password;

  WiFiClient _wifiClient;
  PubSubClient _mqttClient;

  unsigned long _lastReconnectAttempt = 0;
  const unsigned long _reconnectInterval =
      5000; // 5 seconds between reconnect attempts

  std::map<String, MessageCallback> _topicCallbacks;
  std::function<void()> _onConnectCallback = nullptr;

  // Internal callback for message handling
  static void _onMessageReceived(char *topic, byte *payload,
                                 unsigned int length);

  // Pointer to the current instance for the static callback
  static MqttHandler *_instance;

  // Reconnect to the MQTT broker
  bool _reconnect();

  // Process received message
  void _processMessage(const String &topic, const String &message);

  // Subscribe to all saved topics after reconnection
  void _resubscribe();
};

#endif // MQTT_H_
