#include "../include/pirSensor.h"

#include <Arduino.h>
#include <Wire.h>

int totalPeople = -1;
bool newMotion = false;

void initPIR(){
	pinMode(PIRPIN, INPUT);
}

int getPIRState(){
	int state = digitalRead(PIRPIN);
	if(state == LOW){
		if(!newMotion){
			totalPeople += 1;
			newMotion = true;	
		} 
	} else if(state == HIGH){
		newMotion = false;
	}
	Serial.println(totalPeople);
	return totalPeople;
}
