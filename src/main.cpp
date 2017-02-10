#include <Arduino.h>
#include <SoftwareSerial.h>
#include "RGB.h"

#define REDPIN 9
#define GREENPIN 10
#define BLUEPIN 11

#define TXPIN 5
#define RXPIN 8

RGB currentColor = RGB(0, 0, 0);

void setup(){
	pinMode(REDPIN, OUTPUT);
	pinMode(GREENPIN, OUTPUT);
	pinMode(BLUEPIN, OUTPUT);
}

void analogWriteColor(RGB color){
	analogWrite(REDPIN, color.red());
	analogWrite(GREENPIN, color.green());
	analogWrite(BLUEPIN, color.blue());
}

void setColor(RGB color){
	analogWriteColor(color); 
	currentColor = color;
}

int mix(int v0, int v1, float t){
	return (1 - t) * v0 + t * v1;
}

RGB mixColors(RGB color1, RGB color2, float t){
	int r, g, b;
	r = mix(color1.red(), color2.red(), t);
	g = mix(color1.green(), color2.green(), t);
	b = mix(color1.blue(), color2.blue(), t);
	return RGB(r, g, b);
}

void fadeToColor(RGB color, int time){
	time *= 1000;
	int maximumOutput = 255;
	int timeToWait = time/maximumOutput;
	for(int i = 0; i < maximumOutput; i++){
		float a = (float)(i/(float)maximumOutput);
		analogWriteColor(mixColors(currentColor, color, a));
		delay(timeToWait);		
	}
	currentColor = color;
}

void stroboColor(RGB color){
	setColor(color);
	delay(50);
	setColor(RGB(0, 0, 0));
	delay(50);	
}

void loop(){
//	stroboColor(RGB(0, 255, 0));
	/*fadeToColor(RGB(255, 0, 0), 5);
	fadeToColor(RGB(255, 128, 0) ,5);
	fadeToColor(RGB(255, 255, 0), 5);
	fadeToColor(RGB(0, 255, 0), 5);	
	fadeToColor(RGB(0, 255, 255), 5);
	fadeToColor(RGB(0, 0, 255), 5);
	fadeToColor(RGB(255, 0, 255), 5);
	fadeToColor(RGB(255, 0, 175) ,5);*/
	setColor(RGB(0,0,0));
}
