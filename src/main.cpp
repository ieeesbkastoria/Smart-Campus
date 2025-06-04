#include <PubSubClient.h>
#include <WiFi.h>

// WiFi Credentials
constexpr char *ssid = "yourSSID";
constexpr char *password = "yourPassword";

// MQTT Broker Settings
constexpr char *mqttServer = "your.broker.address";
const int mqttPort = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void setupWiFi() {
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

void reconnectMQTT() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("connected!");
      client.publish("esp32/status", "Hello from ESP32");
      client.subscribe("esp32/control");
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
}

void loop() {
  if (!client.connected()) {
    reconnectMQTT();
  }
  client.loop();
}
