#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#include "../include/bme_sensor.h"

/*
 This file incorporates or is based on code from the Adafruit BME680 Library, licensed under the BSD license.
 Copyright (c) Adafruit Industries.
*/

TwoWire bmeI2CBus = TwoWire(0); // Define specific and separate from other buses for the sensor to communicate to and through the ESP32
Adafruit_BME680 bmeSensor(&bmeI2CBus); // Define a BME680 type object and instantiate it as an I2C connected variant explicitly

//This function initialises the Wire I2C bus and Sensor through the use of the functions provided in the corresponding libraries
void initBME680(){
	bmeI2CBus.begin(SDIPIN, SCKPIN); // Begin I2C Wire for specific to sensor bus
	bmeSensor.begin(); // Initialise sensor through provided function from Adafruit's library

	// Initialise all (or specific) parts of the sensor through provided functions and macros inside the Adafruit library
	bmeSensor.setTemperatureOversampling(BME680_OS_8X);
	bmeSensor.setHumidityOversampling(BME680_OS_2X);
	bmeSensor.setPressureOversampling(BME680_OS_4X);
	bmeSensor.setIIRFilterSize(BME680_FILTER_SIZE_3);
	bmeSensor.setGasHeater(320, 150);
}

// This functions gets measurements from the sensor and returns them in a packed struct for easier use
void getReadings(sensorParameters &readings){
	bmeSensor.performReading();
	readings.temp = bmeSensor.temperature;
	readings.atmPressure = (bmeSensor.pressure / 100.0);
	readings.humidity = bmeSensor.humidity;
	readings.gasResistrVal = (bmeSensor.gas_resistance / 1000.0);
	readings.aprxAlt = bmeSensor.readAltitude(PRESSURELVLSEA);
}

