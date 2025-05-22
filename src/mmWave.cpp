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
