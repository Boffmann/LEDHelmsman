#include "RGB.h"

RGB::RGB(int red, int green, int blue){
	_red = red;
	_green = green;
	_blue = blue;
}

RGB::RGB() {
	_red = 0;
	_green = 0;
	_blue = 0;
}

/*
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

*/ 

int RGB::red(){
       	return _red; 
}
int RGB::green(){
       	return _green; 
}
int RGB::blue(){
       	return _blue; 
}

void RGB::setRed(int red){
       	_red = red; 
}
void RGB::setGreen(int green){
       	_green = green; 
}
void RGB::setBlue(int blue){
       	_blue = blue; 
	
}
