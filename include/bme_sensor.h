#ifndef BME680HEADR
#define BME680HEADR

/*
 This file incorporates or is based on code from the Adafruit BME680 Library,
 licensed under the BSD license. Copyright (c) Adafruit Industries.
*/

#include "Adafruit_BME680.h"
#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <Wire.h>

#define PRESSURELVLSEA (1013.25) // Sea level pressure in hPa
#define SCKPIN                                                                 \
  5 // Pin on the ESP32 board that the sensor's S(erial)C(loc)K pin is
    // connected at
#define SDIPIN                                                                 \
  6 // Pin on the ESP32 board taht the sensor's S(erial)DI (data) pin is
    // connected at

/*
        This struct contains the data that is read and returned by the sensor.
        They are all packed in order to avoid creating functions that return
        just one value in the readings. The datatypes are the ones I assume
        are correct and correspond as close to the ones specified in Adafruit's
        Library, if not stated in specific.
*/
typedef struct sParams {
  float temp;             // Ambient temperaure in Celsius.
  float atmPressure;      // Ambient atmospheric pressure in hPa.
  float humidity;         // Humidity reading. Percentage only.
  uint32_t gasResistrVal; // Gas measurement resistor value. kOhm reading only.
  float aprxAlt;          // Approximated altitude.
} sensorParameters;

// Initialisation function
void initBME680();

// Measurement function
void getReadings(sensorParameters &readings);

#endif
