#ifndef BME_SENSOR_H
#define BME_SENSOR_H

#include "Adafruit_BME680.h"
#include <Adafruit_Sensor.h>
#include <Wire.h>

// Declare the BME680 object so it can be used in bme_sensor.cpp
extern Adafruit_BME680 bme;

// Function to initialize the BME680 sensor
bool bmeInit();

// Function to perform a measurement and print the results
void bmeMeasure();

#endif // BME_SENSOR_H