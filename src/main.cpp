#include "../include/DoorSensor.h"
#include "../include/bh1750.h"
#include "../include/mmWave.h"
#include <PubSubClient.h>
#include <WiFi.h>

// WiFi Credentials
constexpr char *ssid = (char *)"i";
constexpr char *password = (char *)"i";

// MQTT Broker Settings
constexpr char *mqttServer = (char *)"192.168.69.2";
const int mqttPort = 1883;

// MQTT Topics Macros
#define ESP32_STATUS_TOPIC "esp32/status"
#define DOOR_TOPIC "Door"
#define LUX_TOPIC "Lx"
#define MOTION_TOPIC "Motion"

WiFiClient espClient;
PubSubClient client(espClient);

static void setupWiFi() {
  delay(100);
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

static void setupSensors() {
  initDoor();
  initBH1750();
  init_mmWave();
}

static void reconnectMQTT() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("connected!");
      client.publish(ESP32_STATUS_TOPIC, "ESP32 Connected");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5s...");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setupWiFi();
  client.setServer(mqttServer, mqttPort);

  setupSensors();
}

void loop() {
  if (!client.connected()) {
    reconnectMQTT();
  }
  client.loop();

  client.publish(LUX_TOPIC, String(computeLx()).c_str());
  client.publish(DOOR_TOPIC, readDoor() ? "Open" : "Closed");
  client.publish(MOTION_TOPIC, String(readAndProcessSensorLines()).c_str());

  // Temp delay for testing
  delay(1000);
}
