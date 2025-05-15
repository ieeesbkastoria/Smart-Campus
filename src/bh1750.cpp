#include "../include/bh1750.h"

#include <Arduino.h>
#include <Wire.h>

void initialise(void){
/*
	This function does some basic configuration
	and initialisation of the sensor.
*/

	Wire.beginTransmission(I2CADDR);
	Wire.write(0x10); // Resolution time between lux reading (120ms)
	Wire.endTransmission();
}

int getSensorData(byte* data){
/*
	This function gets the raw data from the sensor
	and places it in a buffer (here, a pointer to the
	buffer). It should be 2 bytes of data, according
	to the documentation.
*/

	int byteCount = 0; // Works as an index too
	Wire.beginTransmission(I2CADDR);
	Wire.requestFrom(I2CADDR, 2);

	while(Wire.available()){ // While there is data (a byte) to read
		data[byteCount] = Wire.read(); // place it into the buffer at position i
		byteCount++; // and increase the index ( => + data amount)
	}

	Wire.endTransmission();
	return byteCount;
}

uint16_t computeLx(void){
/*
	This function computes the Lux (Lx) amount
	of light present in a space, using the data
	provided from the getSensorData() function,
	and returns it to the place that called this
	func.
*/
	byte buffer[2];
	getSensorData(buffer);

	/*
	   Check if we got the right amount of bytes.
	   In the dfRobot documentation, the count is 2
	*/

	if( 2 == getSensorData() ){
		uint16_t lxCount = ( (data[0] << 8 ) | data[1] ) / 1.2;
	}

	logf(F("\n BH1750: %d Lx", lxCount); // Use logging function from logging.cpp
	return lxCount;
}
