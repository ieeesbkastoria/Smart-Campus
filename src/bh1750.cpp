#include "../include/bh1750.h"

#include <Arduino.h>
#include <Wire.h>

/*
        This function does some basic configuration
        and initialisation of the sensor. In case of
        an error, report it back
*/
bool initBH1750() {
  Wire.begin(SDAPIN, SCLPIN);
  Wire.beginTransmission(I2CADDR);
  Wire.write(RESMODEFREQ);
  uint8_t status = Wire.endTransmission();

  return (status == 0);
}

/*
        This function gets the raw data from the sensor
        and places it in a buffer (here, a pointer to the
        buffer). It should be 2 bytes of data, according
        to the documentation.
*/
int getSensorData(uint8_t *data) {

  int byteCount = 0; // Works as an index too
  Wire.requestFrom(I2CADDR, EXPECTEDBYTES);

  while ((byteCount < EXPECTEDBYTES) &&
         Wire.available()) {       // While there is data (a byte) to read
    data[byteCount] = Wire.read(); // place it into the buffer at position i
    byteCount++;                   // and increase the index ( => + data amount)
  }

  return byteCount;
}

/*
        This function computes the Lux (Lx) amount
        of light present in a space, using the data
        provided from the getSensorData() function,
        and returns it to the place that called this
        func.
*/
uint16_t computeLx() {

  uint8_t buffer[2];
  uint16_t lxCount;

  /*
     Check if we got the right amount of bytes.
     In the dfRobot documentation, the count is 2
  */

  if (2 == getSensorData(buffer)) {
    // TODO: Search documentation for magic number 1.2
    lxCount = ((buffer[0] << 8) | buffer[1]) / 1.2;
  }

  return lxCount;
}
