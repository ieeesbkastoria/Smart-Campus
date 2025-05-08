#include "../include/logging.h"
#include <cstddef>
#include <stdio.h>

/// @brief Formats a PROGMEM string using a `va_list`, similar to `vsnprintf`.
/// @param buf The buffer to write the formatted string into.
/// @param bufsize The size of the output buffer in bytes.
/// @param fmt A format string stored in flash memory (PROGMEM).
/// @param args A `va_list` containing the format arguments.
/// @return The number of characters that would have been written,
///         not including the null terminator.
static std::size_t flash_vsnprintf(char *buf, size_t bufsize,
                                   const __FlashStringHelper *fmt,
                                   va_list args) {
    char fmtBuf[64];
    strncpy_P(fmtBuf, reinterpret_cast<const char *>(fmt), sizeof(fmtBuf));
    fmtBuf[sizeof(fmtBuf) - 1] = '\0';
    return vsnprintf(buf, bufsize, fmtBuf, args);
}
