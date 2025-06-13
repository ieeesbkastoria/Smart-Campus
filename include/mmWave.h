#ifndef MMWAVE_H
#define MMWAVE_H

// Define the pins for our secondary hardware serial (Serial2)
#define RX2_PIN 19
#define TX2_PIN 15

// Define range prefix to identify lines from the sensor
#define RANGE_PREFIX "Range "

#include <Arduino.h>

void sendHexData(String hexString);
int readAndProcessSensorLines();
void init_mmWave();

#endif