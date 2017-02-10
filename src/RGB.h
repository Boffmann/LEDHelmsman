#ifndef RGB_H
#define RGB_H

class RGB{
private:
	int _red;
	int _green;
	int _blue;

public:
	RGB(int red, int green, int blue); 

	int red();
	int green();
	int blue();

	void setRed(int red);
	void setGreen(int green);
	void setBlue(int blue);
	

};

#endif
