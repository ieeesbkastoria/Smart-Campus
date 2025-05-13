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

// logf overloaded function for a single paramenter
auto logf(const __FlashStringHelper *fmt) -> void;

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
 *
 * @notes This logging function consumes a lot of system resources and thus
 * should be used scarcely.
 */
template <typename... Args>
auto logf(const __FlashStringHelper *fmt, Args... args) -> void {
    constexpr std::size_t BUF_SIZE = 128;
    char buffer[BUF_SIZE];

    // Convert __FlashStringHelper to char* for formatting
    PGM_P p = reinterpret_cast<PGM_P>(fmt);

    // Copy the format string from flash to RAM
    char format[BUF_SIZE];
    size_t i = 0;
    while (i < BUF_SIZE - 1) {
        unsigned char c = pgm_read_byte(p++);
        format[i++] = c;
        if (c == 0)
            break;
    }
    format[BUF_SIZE - 1] = 0; // Ensure null termination

    // Format the string with the arguments
    int result = snprintf(buffer, BUF_SIZE, format, args...);

    // Print the prefix
    Serial.print(F("SmartCampus Log | "));

    // Write the formatted string
    if (result >= 0) {
        if (result >= BUF_SIZE) { // Message was truncated
            Serial.write(buffer, BUF_SIZE - 1);
            Serial.println(" [truncated]");
        } else {
            Serial.println(buffer);
        }
    } else { // Encoding error
        Serial.println(F("Error formatting output"));
    }
}

#endif // LOGGING_H_
