#ifndef BH1750_H
#define BH1750_H

#include <Wire.h>
#include <Arduino.h>
#define I2CADDR 0x23 // I2C Address for sensor
#define RESMODEFREQ 0x10 // Resolution time between sensor reading (120ms)
#define EXPECTEDBYTES 2

// Function to init sensor with
bool initBH1750();
// Get raw sensor data func
int getSensorData(uint8_t* data);
// Compute Lx with some computations
uint16_t computeLx();

#endif
