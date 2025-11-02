/**
 * @file bh1750.hpp
 * @brief BH1750 Digital Ambient Light Sensor I2C Driver
 *
 * This module provides an interface for communicating with the BH1750 digital
 * ambient light sensor over the I2C protocol. It handles sensor initialization,
 * raw data acquisition, and light intensity (lux) computation.
 *
 *
 * @note This driver is configured for ESP32 microcontroller
 * @see https://www.rohm.com/documents/11308/3132/bh1750fvi-e.pdf
 */

#ifndef BH1750_H
#define BH1750_H

#include <Arduino.h>
#include <Wire.h>

/**
 * @defgroup BH1750_Config BH1750 Configuration Constants
 * @{
 */

/** @brief I2C slave address of the BH1750 sensor */
#define I2CADDR 0x23

/**
 * @brief Operation mode register value
 *
 * Configures the sensor for Continuous High-Resolution mode with:
 * - Continuous measurement (no power sleep between readings)
 * - High resolution mode (1 lux precision)
 * - 120ms integration time for accurate readings
 *
 * @see BH1750 Datasheet - Mode Selection (0x10 = Continuous High-Res Mode)
 */
#define RESMODEFREQ 0x10

/** @brief Expected number of bytes to read from I2C bus */
#define EXPECTEDBYTES 2

/**
 * @brief GPIO pin for I2C Serial Clock (SCL) on ESP32
 *
 * This pin connects to the BH1750 sensor's SCL line for I2C clock signal
 */
#define SCLPIN 11

/**
 * @brief GPIO pin for I2C Serial Data (SDA) on ESP32
 *
 * This pin connects to the BH1750 sensor's SDA line for I2C data signal
 */
#define SDAPIN 12

/** @} */

/**
 * @brief Initialize the BH1750 ambient light sensor
 *
 * Configures the I2C communication interface with the specified pins (SCLPIN,
 * SDAPIN) and sets the sensor to the continuous high-resolution measurement
 * mode (RESMODEFREQ). This function must be called once during system
 * initialization before any sensor readings can be performed.
 *
 * @return @c true if initialization was successful
 * @return @c false if initialization failed (e.g., sensor not responding on I2C
 * bus)
 *
 * @note Must be called before calling getSensorData() or computeLx()
 * @see getSensorData(), computeLx()
 */
bool initBH1750();

/**
 * @brief Retrieve raw sensor data from the BH1750
 *
 * Reads the 16-bit raw illuminance value from the sensor via I2C protocol.
 * The data is expected to be in big-endian format (MSB first) as per BH1750
 * datasheet. This function blocks until data is available or a timeout occurs.
 *
 * @param[out] data Pointer to a uint8_t array of at least 2 bytes to store
 *                  the raw sensor data (MSB in data[0], LSB in data[1])
 *
 * @return Number of bytes successfully read from the I2C bus
 * @retval 2 if successful (expected number of bytes)
 * @retval <2 if an error occurred or fewer bytes were received
 *
 * @pre initBH1750() must have been called successfully
 * @pre @p data must point to a valid buffer of at least 2 bytes
 *
 * @see initBH1750(), computeLx()
 */
int getSensorData(uint8_t *data);

/**
 * @brief Compute illuminance in lux from raw sensor data
 *
 * Converts the raw 16-bit sensor reading into a light intensity value in lux
 * (lx). The conversion factors depend on the sensor's resolution mode
 * (RESMODEFREQ). For Continuous High-Resolution mode (1 lx precision), the raw
 * value is typically divided by 1.2 to obtain lux.
 *
 * @return Illuminance value in lux as a 16-bit unsigned integer
 * @retval 0 if the sensor has not been read or data is unavailable
 *
 * @pre initBH1750() must have been called successfully
 * @pre getSensorData() should have been called to populate internal sensor
 * buffer
 *
 * @note This function assumes the sensor is operating in RESMODEFREQ mode.
 *       If the operation mode changes, the conversion factor may need
 * adjustment.
 *
 * @see getSensorData(), RESMODEFREQ
 */
uint16_t computeLx();

#endif // BH1750_H
