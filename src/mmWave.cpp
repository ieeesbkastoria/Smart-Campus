#include "mmWave.h"

#include <Arduino.h>
#include <SoftwareSerial.h>


// Definition of the software serial object
SoftwareSerial mySerial(5, 4);  // RX, TX

void sendHexData(String hexString) {
  // Convert hex string to bytes
  int hexStringLength = hexString.length();
  byte hexBytes[hexStringLength / 2];
  
  for (int i = 0; i < hexStringLength; i += 2) {
    hexBytes[i / 2] = strtoul(hexString.substring(i, i + 2).c_str(), NULL, 16);
  }
  
  // Send bytes through software serial
  mySerial.write(hexBytes, sizeof(hexBytes));
}

void readSerialData() {
  // Read and print data from software serial
  while (mySerial.available() > 0) {
    char incomingByte = mySerial.read();
    // old serial print Serial.print(incomingByte);
    logf(F("mmWave : ", incomingByte));
  }
}