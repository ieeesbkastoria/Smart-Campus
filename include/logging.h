/**
 * @file logging.h
 * @brief Utility functions for formatted logging over Serial in Arduino.
 *
 * This header provides a lightweight, memory-efficient way to print
 * formatted strings to the Serial port using format strings stored in
 * flash memory (`PROGMEM`). It is designed for use in resource-constrained
 * microcontroller environments such as Arduino.
 *
 * Use the `logf` function as a drop-in replacement for `printf`,
 * with the `F()` macro to ensure format strings are stored in flash.
 */

#ifndef LOGGING_H_
#define LOGGING_H_

#include <Arduino.h>
#include <cstddef>
#include <stdarg.h>

/** @brief Prints a formatted string to the Serial port using a PROGMEM format
 * string.
 *
 * This function uses a fixed-size buffer and supports format strings stored in
 * flash memory using the `F()` macro. It internally calls `flash_vsnprintf`
 * and writes the result to `Serial`.
 *
 * @tparam Args Variadic list of format arguments.
 * @param fmt A format string stored in flash memory (use F("...")).
 * @param args The format arguments to apply.
 */
template <typename... Args>
auto logf(const __FlashStringHelper *fmt, Args &&...args) -> void {
    constexpr std::size_t BUF_SIZE = 128;
    constexpr const char prefix[] PROGMEM = "SmartCampus Log | ";
    char buffer[BUF_SIZE];

    va_list v;
    va_start(v, fmt);
    std::size_t result = flash_vsnprintf(buffer, BUF_SIZE, fmt, v);
    va_end(v);

    Serial.write((__FlashStringHelper *)prefix);

    // Write the formatted string
    if (result >= 0) {
        if (result >= BUF_SIZE) {
            // Message was truncated
            Serial.write(buffer, BUF_SIZE - 1);
            Serial.println(" [truncated]");
        } else {
            Serial.println(buffer);
        }
    } else {
        // Encoding error
        Serial.println(F("Error formatting output"));
    }
}

#endif // LOGGING_H_
