
#include "../include/DoorSensor.h"
#include <Arduino.h>

// Function to initialize the door sensor
void initDoor() { pinMode(DOOR_SENSOR_PIN, INPUT_PULLUP); }

// Function to read the door sensor state
// Returns the state of the door sensor (false if closed, true if open)
bool readDoor() {

  bool doorState = digitalRead(DOOR_SENSOR_PIN);

  return doorState;
}