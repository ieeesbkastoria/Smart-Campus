#ifndef MMWAVE_H
#define MMWAVE_H

// Define the pins for our secondary hardware serial (Serial2)
#define RX2_PIN 19
#define TX2_PIN 20

#include <Arduino.h>

void sendHexData(String hexString);
void readAndProcessSensorLines();

#endif