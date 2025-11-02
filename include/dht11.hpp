/**
 * @file dht11.hpp
 * @brief DHT11 Temperature and Humidity Sensor Interface Wrapper
 *
 * This module provides a C++ class interface for the DHT11 digital temperature
 * and humidity sensor. It encapsulates sensor initialization, data acquisition,
 * and environmental calculations (heat index) in a clean, object-oriented API.
 *
 * @note This driver wraps the Adafruit DHT library for ease of use
 * @see https://www.adafruit.com/product/386
 * @see https://github.com/adafruit/DHT-sensor-library
 */

#ifndef DHT11_H_
#define DHT11_H_

#include "DHT.h"

/**
 * @defgroup DHT11_Config DHT11 Configuration Constants
 * @{
 */

/**
 * @brief GPIO pin number connected to the DHT11 sensor's data line
 *
 * This digital pin receives the single-wire protocol data from the DHT11
 * sensor. Ensure this pin is configured as an input on the microcontroller.
 */
#define DHTPIN 4

/** @} */

/**
 * @class DHT11Interface
 * @brief Object-oriented interface for DHT11 temperature and humidity sensor
 *
 * This class provides a complete interface for reading temperature, humidity,
 * and computed heat index from a DHT11 sensor. The sensor communicates via
 * a single-wire digital protocol on pin DHTPIN.
 *
 * @note All temperature values are in Celsius; humidity values are in
 * percentage
 * @note Sensor readings have typical accuracy of ±2°C and ±5% RH
 * @note Minimum time between successful reads is approximately 2 seconds
 *
 * @see DHT11 Datasheet for detailed specifications
 */
class DHT11Interface {
public:
  /**
   * @brief Construct a new DHT11 interface object
   *
   * Creates a new DHT11Interface instance for the specified GPIO pin.
   * The sensor is not initialized until begin() is called.
   *
   * @param[in] pin GPIO pin number connected to DHT11 data line
   *
   * @note Constructor does not perform I/O operations; it only initializes
   *       internal state. Call begin() to start sensor communication.
   *
   * @see begin()
   */
  DHT11Interface(uint8_t pin);

  /**
   * @brief Initialize the DHT11 sensor
   *
   * Performs initial setup of the sensor on the specified pin and sets the
   * sensor type to DHT11. This function must be called once during system
   * initialization before any sensor readings can be performed.
   *
   * After initialization, the sensor will be ready to accept read requests.
   * Allow at least 1 second after calling begin() before the first read() call.
   *
   * @return void
   *
   * @pre The GPIO pin specified in the constructor must be available and
   * properly configured
   * @post The sensor is ready for read operations via read()
   *
   * @note This function may block briefly during initialization
   *
   * @see read(), DHT11 Datasheet - Power-up time requirements
   */
  void begin();

  /**
   * @brief Read current temperature, humidity, and heat index from sensor
   *
   * Performs a complete sensor read cycle, retrieving the current temperature
   * and humidity values from the DHT11 sensor. If both values are successfully
   * read, the heat index is automatically calculated and the reading is marked
   * as valid.
   *
   * This operation blocks until the sensor responds or times out (typically
   * ~250ms). The DHT11 requires approximately 2 seconds between successful read
   * cycles.
   *
   * @return @c true if the read was successful and sensor values are valid
   * @return @c false if the read failed (sensor timeout, checksum error, etc.)
   *
   * @post On success: getHumidity(), getTemperature(), getHeatIndex(), and
   *       isValid() return current sensor values
   * @post On failure: previous values are retained; isValid() returns @c false
   *
   * @note Multiple rapid calls (within 2 seconds) may return @c false
   * @note Call isValid() to check if the most recent read was successful
   *
   * @see getHumidity(), getTemperature(), getHeatIndex(), isValid()
   */
  bool read();

  /**
   * @brief Get the relative humidity percentage from the last successful read
   *
   * Returns the humidity value acquired during the most recent successful
   * sensor read operation.
   *
   * @return Relative humidity as a floating-point percentage (0.0 to 100.0)
   * @retval 0.0 if no successful read has been performed
   *
   * @post If isValid() returns @c false, this value is stale (from previous
   * read)
   *
   * @note Typical DHT11 accuracy: ±5% RH
   * @note This is a const member function and does not modify sensor state
   *
   * @see read(), isValid(), getTemperature()
   */
  float getHumidity() const;

  /**
   * @brief Get the temperature in Celsius from the last successful read
   *
   * Returns the temperature value acquired during the most recent successful
   * sensor read operation.
   *
   * @return Temperature in Celsius as a floating-point value
   * @retval 0.0 if no successful read has been performed
   *
   * @post If isValid() returns @c false, this value is stale (from previous
   * read)
   *
   * @note Typical DHT11 accuracy: ±2°C
   * @note Operating range: 0°C to 50°C
   * @note This is a const member function and does not modify sensor state
   *
   * @see read(), isValid(), getHumidity(), getHeatIndex()
   */
  float getTemperature() const;

  /**
   * @brief Get the computed heat index from the last successful read
   *
   * Returns the computed heat index (apparent temperature) based on the most
   * recent temperature and humidity readings. The heat index is a measure of
   * how hot it feels to the human body when combined effects of temperature
   * and humidity are considered.
   *
   * Heat index is only meaningful when temperature is above 26.7°C (80°F).
   * Below this threshold, this function may return the actual temperature.
   *
   * @return Apparent temperature (heat index) in Celsius as a floating-point
   * value
   * @retval temperature if below the heat index calculation threshold
   * @retval 0.0 if no successful read has been performed
   *
   * @post If isValid() returns @c false, this value is stale (from previous
   * read)
   *
   * @note Heat index is calculated automatically after each successful read()
   * @note This is a const member function and does not modify sensor state
   *
   * @see read(), getTemperature(), getHumidity(), calculateHeatIndex()
   */
  float getHeatIndex() const;

  /**
   * @brief Check if the last sensor reading was valid
   *
   * Indicates whether the most recent read() operation was successful.
   * A valid reading means the sensor data was acquired without errors and
   * all derived values (temperature, humidity, heat index) are current.
   *
   * @return @c true if the last read() was successful and values are current
   * @return @c false if the last read() failed or no read has been performed
   * yet
   *
   * @note Before using sensor values, check this function to ensure data
   * freshness
   * @note This is a const member function and does not modify sensor state
   *
   * @see read(), getLastReadTime()
   */
  bool isValid() const;

  /**
   * @brief Get the timestamp of the last successful sensor read
   *
   * Returns the system timestamp (in milliseconds since boot) of when the most
   * recent successful sensor read was completed.
   *
   * @return Timestamp in milliseconds (from millis()) of last successful read
   * @retval 0 if no successful read has been performed yet
   *
   * @note Use this value to determine when the next read should be performed
   * @note DHT11 requires ~2 seconds between successive reads
   * @note This is a const member function and does not modify sensor state
   *
   * @see read(), isValid()
   */
  unsigned long getLastReadTime() const;

private:
  /** @brief DHT sensor object (Adafruit DHT library) */
  DHT dht;

  /** @brief Last read relative humidity (percentage, 0-100) */
  float humidity;

  /** @brief Last read temperature in Celsius */
  float temperature;

  /** @brief Last computed heat index in Celsius */
  float heatIndex;

  /** @brief Validity flag for the most recent sensor read */
  bool validReading;

  /** @brief Timestamp (milliseconds) of the last successful read */
  unsigned long lastReadTime;

  /**
   * @brief Calculate the heat index from current temperature and humidity
   *
   * Computes the apparent temperature (heat index) using the temperature
   * and humidity values stored in member variables. This function uses a
   * simplified regression formula suitable for most applications.
   *
   * The heat index is only meaningful when:
   * - Temperature >= 26.7°C (80°F)
   * - Humidity is in a realistic range
   *
   * For conditions outside this range, the actual temperature is used.
   *
   * @return void (updates the heatIndex member variable)
   *
   * @pre temperature and humidity must contain valid sensor readings
   * @post heatIndex is updated with the computed apparent temperature
   *
   * @note This function is called automatically by read() after successful
   * reads
   * @note This is a private member function
   *
   * @see read(), getHeatIndex()
   */
  void calculateHeatIndex();
};

#endif // DHT11_H_
