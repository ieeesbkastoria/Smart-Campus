/**
 * @file config.h
 * @brief Central configuration for a Smart Campus sensor node
 *
 * Collects every per-deployment setting in one place: GPIO pin assignments,
 * MQTT broker address, timing intervals and MQTT topic names. Adjust the
 * values here to match your board wiring and network.
 *
 * @note WiFi credentials are kept separately in secrets.h (git-ignored)
 */

#ifndef CONFIG_H
#define CONFIG_H

/**
 * @defgroup Pin_Config GPIO Pin Assignments
 * @{
 */

/**
 * @brief GPIO pin number connected to the DHT11 sensor's data line
 *
 * This digital pin receives the single-wire protocol data from the DHT11
 * sensor. Ensure this pin is configured as an input on the microcontroller.
 */
#define DHTPIN 4

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
 * @defgroup MQTT_Config MQTT Broker Settings
 * @{
 */

/** @brief Hostname or IP address of the MQTT broker */
#define MQTT_SERVER "192.168.69.2"

/** @brief TCP port of the MQTT broker */
#define MQTT_PORT 1883

/** @} */

/**
 * @defgroup Timing_Config Timing Intervals
 * @{
 */

/** @brief Interval between sensor readings published to MQTT (milliseconds) */
#define PUBLISH_INTERVAL_MS 5000UL

/** @brief Delay before retrying a failed MQTT connection (milliseconds) */
#define MQTT_RETRY_INTERVAL_MS 5000UL

/** @} */

/**
 * @defgroup Topic_Config MQTT Topic Names
 * @{
 */

/** @brief Node connection status messages */
#define ESP32_STATUS_TOPIC "esp32/status"

/** @brief Door state ("Open" / "Closed") */
#define DOOR_TOPIC "Door"

/** @brief Illuminance in lux */
#define LUX_TOPIC "Lx"

/** @brief Motion detection (reserved, not yet published) */
#define MOTION_TOPIC "Motion"

/** @brief Temperature in Celsius */
#define TEMP_TOPIC "Temperature"

/** @brief Heat index (felt temperature) in Celsius */
#define FELT_TEMP "FeltTemperature"

/** @brief Atmospheric pressure (reserved, not yet published) */
#define PRESSURE_TOPIC "Pressure"

/** @brief Relative humidity in percent */
#define HUMIDITY_TOPIC "Humidity"

/** @} */

#endif // CONFIG_H
