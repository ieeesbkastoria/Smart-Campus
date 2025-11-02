/**
 * @file DoorSensor.hpp
 * @brief Door State Sensor Interface Module
 *
 * This module provides a simple interface for reading the state of a door
 * sensor connected to a digital GPIO pin. It supports initialization and
 * polling of the door's open/closed state, making it suitable for security
 * systems, automated access control, and IoT applications.
 *
 * The door sensor is expected to be a digital switch that provides either a
 * HIGH (door open) or LOW (door closed) signal on the specified GPIO pin.
 *
 * @author Turtel216
 * @date 2025-11-02
 * @version 1.0
 *
 * @note This module assumes a pull-up or pull-down resistor is properly
 * configured on the GPIO pin to ensure stable readings
 * @see https://en.wikipedia.org/wiki/Door_switch
 */

#ifndef DOOR_SENSOR_H
#define DOOR_SENSOR_H

#include <Arduino.h>

/**
 * @defgroup DoorSensor_Config Door Sensor Configuration Constants
 * @{
 */

/**
 * @brief GPIO pin number connected to the door sensor
 *
 * This digital pin reads the state of the door sensor switch. The pin should be
 * configured as an INPUT with appropriate pull-up or pull-down resistor to
 * ensure stable and noise-free readings.
 *
 * @note Ensure this pin is not used by other peripherals
 * @note Add debouncing logic if the sensor exhibits switch bounce
 */
#define DOOR_SENSOR_PIN 13

/** @} */

/**
 * @brief Initialize the door sensor
 *
 * Configures the GPIO pin (DOOR_SENSOR_PIN) as a digital input and prepares
 * the door sensor for state polling. This function must be called once during
 * system initialization before any door state readings can be performed.
 *
 * After initialization, the sensor is ready to accept state queries via
 * readDoor().
 *
 * @return void
 *
 * @pre The GPIO pin specified by DOOR_SENSOR_PIN must be available and not
 *      already configured for another purpose
 * @post DOOR_SENSOR_PIN is configured as a digital INPUT and ready for polling
 *
 * @note This function should be called during system setup
 * @note Calling this function multiple times is safe but unnecessary
 *
 * @see readDoor(), DOOR_SENSOR_PIN
 */
void initDoor();

/**
 * @brief Read the current state of the door sensor
 *
 * Polls the digital input pin connected to the door sensor and returns the
 * current door state. This is a non-blocking read operation that samples the
 * GPIO pin's current voltage level.
 *
 * @return @c true if the door is open (or sensor reads HIGH)
 * @return @c false if the door is closed (or sensor reads LOW)
 *
 * @pre initDoor() must have been called successfully
 *
 * @note This function performs a single read without debouncing
 * @note For sensitive applications, implement debouncing logic around this
 * function
 * @note Repeated calls return the current instantaneous state; use state
 * tracking for edge detection (door opening/closing transitions)
 *
 * @warning GPIO pin voltage fluctuations or switch bounce may cause spurious
 *          state changes. Consider implementing debouncing if state instability
 *          is observed.
 *
 * @see initDoor(), DOOR_SENSOR_PIN
 */
bool readDoor();

#endif // DOOR_SENSOR_Hf
