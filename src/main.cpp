#include <Arduino.h>
#include <SoftwareSerial.h>
#include "RGB.h"
#include "Bluetooth.h"

const int RX = 2;
const int TX = 3;
const int BLUEPIN = 6;
const int REDPIN = 9;
const int GREENPIN = 10;

unsigned char data = ' ';

SoftwareSerial BTSerial(RX, TX);
RGB currentColor(255, 255, 255);
float _brightness;
unsigned char onOff;

void analogWriteColor(RGB color){
	int red = color.red() * _brightness * onOff;
	int green = color.green() * _brightness * onOff;
	int blue = color.blue() * _brightness * onOff;
	analogWrite(REDPIN, red);
	analogWrite(GREENPIN, green);
	analogWrite(BLUEPIN, blue);
	Serial.print("OnOff: ");
	Serial.println((int)onOff);
	Serial.print("Brightness: ");
	Serial.println(_brightness);
	Serial.print("Red: ");
	Serial.println(red);
	Serial.print("Green");
	Serial.println(green);
	Serial.print("Blue");
	Serial.println(blue);
	
	currentColor = color;
}

void fadeToColor(RGB color, int time){
	time *= 1000;
	int maximumOutput = 255;
	int timeToWait = time/maximumOutput;
	for(int i = 0; i < maximumOutput; i++){
		float a = (float)(i/(float)maximumOutput);
		analogWriteColor(RGB::mixColors(currentColor, color, a));
		delay(timeToWait);		
	}
	currentColor = color;
}

void validateSendData(unsigned char processingSuccessful) {
	if (processingSuccessful) {
		Serial.println("Checksum correct");
	} else {
		Serial.println("Checksum is not correct");
	}
	BTSerial.print(processingSuccessful);
}

void setOnOff(unsigned char data, unsigned char processingSuccessful) {
	//validateSendData(processingSuccessful);
	Serial.print("ONOFF: ");
	Serial.println((int) data);

	onOff = data;
	analogWriteColor(currentColor);
}

void setBrightness(unsigned char brightness, unsigned char processingSuccessful) {
	//validateSendData(processingSuccessful);
	Serial.print("Set Brightness: ");
	if (processingSuccessful) {
		Serial.println("Checksum correct");
	} else {
		Serial.println("Checksum is not correct");
	}
	Serial.println((int) brightness);

	_brightness = (float)brightness / 100.0;
	analogWriteColor(currentColor);
}

void setColor(RGB color, unsigned char processingSuccessful) {
	//validateSendData(processingSuccessful);
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

	analogWriteColor(color);
}

Bluetooth bluetooth(&setOnOff, &setBrightness, &setColor);

void setup(){
	Serial.begin(9600); // Default communication rate of the Bluetooth module
	BTSerial.begin(9600);
	pinMode(REDPIN, OUTPUT);
	pinMode(GREENPIN, OUTPUT);
	pinMode(BLUEPIN, OUTPUT);
	_brightness = 1.0;
	onOff = 1;
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
