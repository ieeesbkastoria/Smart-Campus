#include "../include/bh1750.h"

#include <Arduino.h>
#include <Wire.h>

/*
        This function does some basic configuration
        and initialisation of the sensor. In case of
        an error, report it back
*/
bool initBH1750() {
  Wire.begin(SDAPIN, SCLPIN); // Start Wire at specified pins (see header file if needed to be customised)
  Wire.beginTransmission(I2CADDR);
  Wire.write(RESMODEFREQ); // Write specified mode to sensor (see header file)
  uint8_t status = Wire.endTransmission(); // End transmission and get the return status

  return (status == 0); // If everything went well, this should return TRUE
}

/*
        This function gets the raw data from the sensor
        and places it in a buffer (here, a pointer to the
        buffer). It should be 2 bytes of data, according
        to the documentation.
*/
int getSensorData(uint8_t *data) {

  int byteCount = 0; // Works as an index too
  Wire.requestFrom(I2CADDR, EXPECTEDBYTES); // Get bytes from bus

  while ((byteCount < EXPECTEDBYTES) &&
         Wire.available()) {       // While there is data (a byte) to read
    data[byteCount] = Wire.read(); // place it into the buffer at position [byteCount]
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
    // Manipulate bytes in buffer to get reading
    /*
	1) Shift high-byte 8 bits to the left to create space for lower byte
	2) Logical-OR lower-byte with higher-byte to combine them
	3) Divide with 1.2 to account for internal sensor characteristics (specific to this sensor, check ROHM BH1750FVI datasheet. Should be same or similar with the Fermion BH1750 sensor)

	NOTE: If customising the operation mode, or sensitivity, take account for them by multiplying this result with (MTreg / 69), where MTreg is your custom measurement time register value. The default is 69milisec and is ommited.
	*/
    lxCount = ((buffer[0] << 8) | buffer[1]) / 1.2;
  }

  return lxCount;
}

