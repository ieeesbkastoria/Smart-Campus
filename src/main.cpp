#include "../include/DoorSensor.h"
#include "../include/bh1750.h"
#include "../include/bme_sensor.h"
#include "../include/mmWave.h"
#include <PubSubClient.h>
#include <WiFi.h>

// WiFi Credentials
const char *ssid = "IEEE Lab";
const char *password = "IEEE@2025";

// MQTT Broker Settings
const char *mqttServer = "192.168.69.2";
const int mqttPort = 1883;

// MQTT Topics Macros
#define ESP32_STATUS_TOPIC "esp32/status"
#define DOOR_TOPIC "Door"
#define LUX_TOPIC "Lx"
#define MOTION_TOPIC "Motion"
#define TEMP_TOPIC "Temperature"
#define PRESSURE_TOPIC "Pressure"
#define HUMIDITY_TOPIC "Humidity"
#define GAS_TOPIC "Gas"

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastPublish = 0;
const unsigned long publishInterval = 5000; // 5 seconds

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
  initBME680();
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

// Publish data to mqtt and print error on failure
static bool publishWithCheck(const char *topic, const char *payload) {
  if (client.publish(topic, payload)) {
    return true;
  } else {
    Serial.print("Failed to publish to ");
    Serial.println(topic);
    return false;
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

  unsigned long currentTime = millis();
  if (currentTime - lastPublish >= publishInterval) {
    lastPublish = currentTime;

    publishWithCheck(LUX_TOPIC, String(computeLx()).c_str());
    publishWithCheck(DOOR_TOPIC, readDoor() ? "Open" : "Closed");
    // publishWithCheck(MOTION_TOPIC,
    // String(readAndProcessSensorLines()).c_str());

    sensorParameters bme_data{0.0, 0.0, 0.0, 0, 0.0};
    getReadings(bme_data);

    publishWithCheck(TEMP_TOPIC, String(bme_data.temp).c_str());
    publishWithCheck(PRESSURE_TOPIC, String(bme_data.atmPressure).c_str());
    publishWithCheck(HUMIDITY_TOPIC, String(bme_data.humidity).c_str());
    publishWithCheck(GAS_TOPIC, String(bme_data.gasResistrVal).c_str());
  }

  // Small delay to prevent watchdog issues
  delay(10);
}
