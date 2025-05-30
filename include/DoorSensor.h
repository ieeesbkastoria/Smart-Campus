
#ifndef DOOR_SENSOR_H
#define DOOR_SENSOR_H

#include <Arduino.h>

// Define the pin for the door sensor
#define DOOR_SENSOR_PIN 13

// Function to initialize the door sensor
void initDoor();

// Function to read the door sensor state
bool readDoor();

#endif