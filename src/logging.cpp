#include "../include/logging.h"
#include <cstddef>
#include <stdio.h>

// logf overloaded function for a single paramenter
auto logf(const __FlashStringHelper *fmt) -> void {
    Serial.print(F("SmartCampus Log | "));
    Serial.println(fmt);
}
