#ifndef RGB_H
#define RGB_H

class RGB{
private:
	int _red;
	int _green;
	int _blue;

	static int mix(int v0, int v1, float t){
		return (1 - t) * v0 + t * v1;
	}

public:
	RGB(int red, int green, int blue); 
	RGB();

	int red();
	int green();
	int blue();

	void setRed(int red);
	void setGreen(int green);
	void setBlue(int blue);

	static RGB RGB::mixColors(RGB color1, RGB color2, float t){
		int r, g, b;
		r = mix(color1.red(), color2.red(), t);
		g = mix(color1.green(), color2.green(), t);
		b = mix(color1.blue(), color2.blue(), t);
		return RGB(r, g, b);
	}
};

#endif
