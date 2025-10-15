#ifndef DHT11_H_
#define DHT11_H_

#include "DHT.h"

#define DHTPIN 4 // Digital pin connected to the DHT sensor

class DHT11Interface {
public:
  // Constructor
  DHT11Interface(uint8_t pin);

  // Initialize the sensor
  void begin();

  // Read sensor data (returns true if successful)
  bool read();

  // Getters for sensor values
  float getHumidity() const;
  float getTemperature() const;
  float getHeatIndex() const;

  // Check if last reading was valid
  bool isValid() const;

  // Get last read timestamp
  unsigned long getLastReadTime() const;

private:
  DHT dht;
  float humidity;
  float temperature;
  float heatIndex;
  bool validReading;
  unsigned long lastReadTime;

  // Calculate heat index
  void calculateHeatIndex();
};

#endif // DHT11_H_
