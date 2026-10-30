#include "../include/DoorSensor.hpp"
#include "../include/bh1750.hpp"
#include "../include/dht11.hpp"
#include <PubSubClient.h>
#include <WiFi.h>
#include <cstdio>

// WiFi Credentials (see include/secrets.example.h)
#if __has_include("../include/secrets.h")
#include "../include/secrets.h"
#else
#error "Missing include/secrets.h: copy include/secrets.example.h and fill in your WiFi credentials"
#endif

const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;

// MQTT Broker Settings
const char *mqttServer = "192.168.69.2";
const int mqttPort = 1883;

// Create DHT11 interface instance
DHT11Interface dht(DHTPIN);

// MQTT Topics Macros
#define ESP32_STATUS_TOPIC "esp32/status"
#define DOOR_TOPIC "Door"
#define LUX_TOPIC "Lx"
#define MOTION_TOPIC "Motion"
#define TEMP_TOPIC "Temperature"
#define FELT_TEMP "FeltTemperature"
#define PRESSURE_TOPIC "Pressure"
#define HUMIDITY_TOPIC "Humidity"

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastPublish = 0;
const unsigned long publishInterval = 5000; // 5 seconds

// Whether the BH1750 acknowledged its configuration command
bool bh1750Ready = false;

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
  bh1750Ready = initBH1750();
  if (!bh1750Ready) {
    Serial.println(F("Failed to initialize BH1750 sensor!"));
  }
  dht.begin();
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

    char buffer[1024];

    // Retry initialization in case the sensor was unavailable at boot
    if (!bh1750Ready) {
      bh1750Ready = initBH1750();
    }

    uint16_t lx;
    if (bh1750Ready && computeLx(&lx)) {
      snprintf(buffer, sizeof(buffer), "%u", lx);
      publishWithCheck(LUX_TOPIC, buffer);
    } else {
      // Failed reading, re-initialize on the next cycle
      bh1750Ready = false;
      Serial.println(F("Failed to read from BH1750 sensor!"));
    }

    publishWithCheck(DOOR_TOPIC, readDoor() ? "Open" : "Closed");

    if (dht.read()) {
      // Successful reading

      snprintf(buffer, sizeof(buffer), "%.2f", dht.getHumidity());
      publishWithCheck(HUMIDITY_TOPIC, buffer);

      snprintf(buffer, sizeof(buffer), "%.2f", dht.getTemperature());
      publishWithCheck(TEMP_TOPIC, buffer);

      snprintf(buffer, sizeof(buffer), "%.2f", dht.getHeatIndex());
      publishWithCheck(FELT_TEMP, buffer);
    } else {
      // Failed reading
      Serial.println(F("Failed to read from DHT sensor!"));
    }
  }

  // Small delay to prevent watchdog issues
  delay(10);
}
