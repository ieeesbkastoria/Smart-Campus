#include "../include/bme_sensor.h"
#include "Adafruit_BME680.h"
#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <Wire.h>

Adafruit_BME680 bmeSensor; // Use default I2C

bool initBME680() {
  Wire.begin(SDIPIN, SCKPIN); // Use default Wire object

  if (!bmeSensor.begin(0x77)) {
    if (!bmeSensor.begin(0x76)) {
      return false;
    }
  }

  bmeSensor.setTemperatureOversampling(BME680_OS_8X);
  bmeSensor.setHumidityOversampling(BME680_OS_2X);
  bmeSensor.setPressureOversampling(BME680_OS_4X);
  bmeSensor.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bmeSensor.setGasHeater(320, 150);

  return true;
}

bool getReadings(sensorParameters &readings) {
  if (!bmeSensor.performReading()) {
    return false; // Reading failed
  }

  readings.temp = bmeSensor.temperature;
  readings.atmPressure = (bmeSensor.pressure / 100.0);
  readings.humidity = bmeSensor.humidity;
  readings.gasResistrVal = (bmeSensor.gas_resistance / 1000.0);
  readings.aprxAlt = bmeSensor.readAltitude(PRESSURELVLSEA);

  return true;
}
