#ifndef BH1750_H
#define BH1750_H

#include <Wire.h>
#include <Arduino.h>
#define I2CADDR 0x23 // I2C Address for sensor

void initialise(void); // Function to init sensor with
int getSensorData(byte* data); // Get raw sensor data func
uint16_t computeLx(void); // Compute Lx with some computations

#ifndef
