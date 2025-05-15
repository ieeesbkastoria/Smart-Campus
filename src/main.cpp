#include "../include/mqtt.h"
#include <Arduino.h>
#include <WiFi.h>

// WiFi credentials
const char *ssid = "YOUR_WIFI_SSID";
const char *password = "YOUR_WIFI_PASSWORD";

// MQTT broker details
const char *mqttBroker = "192.168.1.100"; // Replace with your broker IP
const int mqttPort = 1883;
const char *mqttUser = "";     // Leave empty if authentication is not required
const char *mqttPassword = ""; // Leave empty if authentication is not required

// MQTT topics
const char *tempTopic = "esp32/temperature";
const char *humidTopic = "esp32/humidity";
const char *controlTopic = "esp32/control";
const char *statusTopic = "esp32/status";

// Create an instance of the MqttHandler
MqttHandler mqtt("ESP32-Client", mqttBroker, mqttPort, mqttUser, mqttPassword);

// Function declarations
void connectWiFi();
void handleControlMessages(const String &topic, const String &message);
void onMqttConnected();

// Variables for sensor data
float temperature = 0.0;
float humidity = 0.0;
unsigned long lastPublishTime = 0;
const long publishInterval = 10000; // 10 seconds

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  connectWiFi();

  // Set up MQTT
  mqtt.setWill(statusTopic, "offline", true); // Last will message
  mqtt.setOnConnectCallback(onMqttConnected);

  // Connect to the MQTT broker
  if (mqtt.begin()) {
    Serial.println("Connected to MQTT broker");
  } else {
    Serial.println("Failed to connect to MQTT broker");
  }

  // Subscribe to the control topic
  mqtt.subscribe(controlTopic, handleControlMessages);
}

void loop() {
  // Handle MQTT connection and messages
  mqtt.loop();

  // Simulate reading sensor data
  unsigned long currentMillis = millis();
  if (currentMillis - lastPublishTime >= publishInterval) {
    lastPublishTime = currentMillis;

    // Simulated sensor readings
    temperature = random(2000, 3000) / 100.0; // 20.00 to 30.00
    humidity = random(4000, 6000) / 100.0;    // 40.00 to 60.00

    // Format data as JSON
    String tempData =
        "{\"value\":" + String(temperature, 2) + ",\"unit\":\"C\"}";
    String humidData = "{\"value\":" + String(humidity, 2) + ",\"unit\":\"%\"}";

    // Publish sensor data
    mqtt.publish(tempTopic, tempData);
    mqtt.publish(humidTopic, humidData);

    Serial.println("Published temperature: " + String(temperature) + "°C");
    Serial.println("Published humidity: " + String(humidity) + "%");
  }
}

// Connect to WiFi network
void connectWiFi() {
  Serial.println("Connecting to WiFi...");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: " + WiFi.localIP().toString());
}

// Callback for control messages
void handleControlMessages(const String &topic, const String &message) {
  Serial.println("Received message on topic: " + topic);
  Serial.println("Message: " + message);

  // Example: Parse control messages
  if (message == "getStatus") {
    String statusMsg = "{\"temp\":" + String(temperature, 2) +
                       ",\"humidity\":" + String(humidity, 2) +
                       ",\"uptime\":" + String(millis() / 1000) + "}";
    mqtt.publish(statusTopic, statusMsg);
  } else if (message.startsWith("led:")) {
    // Example: Control an LED
    int value = message.substring(4).toInt();
    // You would typically do something with this value
    Serial.println("Setting LED to: " + String(value));
  }
}

// Callback when MQTT connects
void onMqttConnected() {
  Serial.println("MQTT connection established");

  // Publish online status
  mqtt.publish(statusTopic, "online", true);

  // Additional setup after connection if needed
}
