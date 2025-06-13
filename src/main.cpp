#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#include "../include/bme_sensor.h"

void setup(){
	Serial.begin(115200);
	initBME680();
}

void loop(){
	sensorParameters envScreenings; // Define a struct to contain all the sensor readings we can get from the BME680
	getReadings(envScreenings); // Call measurement function and pass struct instance to it

	// Print environment variables
	Serial.print("Temperature: ");
	Serial.print(envScreenings.temp);
	Serial.println("*C");
	Serial.print("Humidity: ");
	Serial.print(envScreenings.humidity);
	Serial.println("%");
	Serial.print("Atmospheric Pressure: ");
	Serial.print(envScreenings.atmPressure);
	Serial.println("hPa");
	Serial.print("Gas Sensor Resistance: ");
	Serial.print(envScreenings.gasResistrVal);
	Serial.println("kOhm");
	Serial.print("Approximated altitude: ");
	Serial.print(envScreenings.aprxAlt);
	Serial.println("m");
	delay(2000);
}
