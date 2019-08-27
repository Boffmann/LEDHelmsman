#include <Arduino.h>
#include <SoftwareSerial.h>
#include "RGB.h"
#include "Bluetooth.h"

const int RX = 2;
const int TX = 3;

unsigned char data = ' ';

SoftwareSerial BTSerial(RX, TX);

void validateSendData(unsigned char processingSuccessful) {
	if (processingSuccessful) {
		Serial.println("Checksum correct");
	} else {
		Serial.println("Checksum is not correct");
	}
	BTSerial.print(processingSuccessful);
}

void setOnOff(unsigned char data, unsigned char processingSuccessful) {
	validateSendData(processingSuccessful);
	Serial.print("ONOFF: ");
	Serial.println((int) data);
}

void setBrightness(unsigned char brighness, unsigned char processingSuccessful) {
	validateSendData(processingSuccessful);
	Serial.print("Set Brightness: ");
	if (processingSuccessful) {
		Serial.println("Checksum correct");
	} else {
		Serial.println("Checksum is not correct");
	}
	Serial.println((int) brighness);
}

void setColor(RGB color, unsigned char processingSuccessful) {
	validateSendData(processingSuccessful);
	if (processingSuccessful) {
		Serial.println("Checksum correct");
	} else {
		Serial.println("Checksum is not correct");
	}
	Serial.print("Set Color Red: ");
	Serial.println((int) color.red());
	Serial.print("Set Color Green: ");
	Serial.println((int) color.green());
	Serial.print("Set Color Blue: ");
	Serial.println((int) color.blue());
}

Bluetooth bluetooth(&setOnOff, &setBrightness, &setColor);

void setup(){
	Serial.begin(9600); // Default communication rate of the Bluetooth module
	BTSerial.begin(9600);
}

void loop(){
	if(BTSerial.available()){ // Checks whether data is comming from the serial port
    	data = BTSerial.read(); // Reads the data from the serial port
		Serial.print("Read data byte: ");
		Serial.println((int) data);
		bluetooth.addDataByte(data);
		bluetooth.processData();
	}
}
