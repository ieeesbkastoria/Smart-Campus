#include "../include/bme_sensor.h"
#include <Arduino.h> // Required for Serial, millis(), delay()
#include <Wire.h>

// Define the BME680 object
// Adafruit_BME680 bme; // Uses I2C

bool bmeInit() {
  Serial.begin(115200);
  while (!Serial) {
    delay(10); // wait for serial port to connect.
  }
  Serial.println(F("BME680 Sensor Initialization"));

  if (!bme.begin()) { // Default I2C address is 0x77, library may also try 0x76
    Serial.println(F("Could not find a valid BME680 sensor, check wiring!"));
    return false;
  }

  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms
  Serial.println(F("BME680 initialized successfully."));
  return true;
}

void bmeMeasure() {
  // Tell BME680 to begin measurement.
  unsigned long endTime = bme.beginReading();
  if (endTime == 0) {
    Serial.println(F("Failed to begin reading :("));
    return;
  }
  // Serial.print(F("Reading started at "));
  // Serial.print(millis());
  // Serial.print(F(" and will finish at "));
  // Serial.println(endTime);

  // Obtain measurement results from BME680.
  if (!bme.endReading()) {
    Serial.println(F("Failed to complete reading :("));
    return;
  }

  // Serial.print(F("Reading completed at "));
  // Serial.println(millis());

  Serial.print(F("Temperature = "));
  Serial.print(bme.temperature);
  Serial.println(F(" *C"));

  Serial.print(F("Pressure = "));
  Serial.print(bme.pressure / 100.0);
  Serial.println(F(" hPa"));

  Serial.print(F("Humidity = "));
  Serial.print(bme.humidity);
  Serial.println(F(" %"));

  Serial.print(F("Gas = "));
  Serial.print(bme.gas_resistance / 1000.0);
  Serial.println(F(" KOhms"));

  Serial.println();
}