#include "../include/dht11.h"

DHT11Interface::DHT11Interface(uint8_t pin)
    : dht(pin, DHT11), humidity(0), temperature(0), heatIndex(0),
      validReading(false), lastReadTime(0) {}

void DHT11Interface::begin() { dht.begin(); }

bool DHT11Interface::read() {
  // Read sensor values
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  // Check if readings are valid
  if (isnan(humidity) || isnan(temperature)) {
    validReading = false;
    return false;
  }

  // Calculate heat index
  calculateHeatIndex();

  validReading = true;
  lastReadTime = millis();
  return true;
}

float DHT11Interface::getHumidity() const { return humidity; }

float DHT11Interface::getTemperature() const { return temperature; }

float DHT11Interface::getHeatIndex() const { return heatIndex; }

bool DHT11Interface::isValid() const { return validReading; }

unsigned long DHT11Interface::getLastReadTime() const { return lastReadTime; }

void DHT11Interface::calculateHeatIndex() {
  heatIndex = dht.computeHeatIndex(temperature, humidity, false);
}
