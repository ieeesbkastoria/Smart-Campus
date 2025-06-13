#ifndef BH1750_H
#define BH1750_H

#include <Arduino.h>
#include <Wire.h>
#define I2CADDR 0x23 // I2C Address for sensor
#define RESMODEFREQ                                                            \
  0x10 // Set sensor operation mode - Continuous High-Res, 120ms time window
       // between readings, 1lx precision
#define EXPECTEDBYTES 2 // Byte amount that we expect to read from the bus
#define SCLPIN                                                                 \
  11 // Pin on ESP32 that the sensor's S(erial)CL(ock) Pin is connected to
#define SDAPIN                                                                 \
  12 // Pin on ESP32 that the sensor's S(erial)DA(ta) Pin is connected to

// Function to init sensor with
bool initBH1750();
// Get raw sensor data func
int getSensorData(uint8_t *data);
// Compute Lx with some computations
uint16_t computeLx();

#endif
