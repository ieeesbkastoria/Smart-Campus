#include "../include/mmWave.h"
#include <Arduino.h>

// Original function to send command bytes - KEEP AS IS
void sendHexData(String hexString)
{
    int hexStringLength = hexString.length();
    if (hexStringLength % 2 != 0)
    {
        Serial.println("Error: Hex string must have an even number of characters.");
        return;
    }
    // Calculate number of bytes and create a buffer
    int byteCount = hexStringLength / 2;
    byte hexBytes[byteCount];

    // Convert each pair of hex characters to a byte
    for (int i = 0; i < hexStringLength; i += 2)
    {
        String byteString = hexString.substring(i, i + 2);
        byte hexByte = (byte)strtoul(byteString.c_str(), NULL, 16);
        hexBytes[i / 2] = hexByte;
    }

    // Debug output: print the bytes being sent
    Serial.print("Sending ");
    Serial.print(byteCount);
    Serial.print(" bytes: ");

    for (int i = 0; i < byteCount; i++)
    {
        if (hexBytes[i] < 16)
            Serial.print("0");
        Serial.print(hexBytes[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    // Send the bytes to the sensor via Serial2
    Serial2.write(hexBytes, byteCount);
}

/*
 Reads data from the mmWave sensor and processes it line by line.
 Currently extracts distance information from lines starting with "Range ".
 */

void readAndProcessSensorLines()
{
    // Get all available data from sensor
    while (Serial2.available() > 0)
    {
        // Read a complete line and remove whitespace
        String line = Serial2.readStringUntil('\n');
        line.trim();

        // Process lines containing range information
        if (line.startsWith(RANGE_PREFIX))
        {
            // Extract the distance value (after "Range " prefix)
            String distanceStr = line.substring(strlen(RANGE_PREFIX));
            int distance = distanceStr.toInt();

            Serial.print("Detected Distance: ");
            Serial.print(distance);
            Serial.println(" cm");
        }
    }
}