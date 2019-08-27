#ifndef _BLUETOOTH_H_
#define _BLUETOOTH_H_

#include "RGB.h"
#include "Arduino.h"

#define ONOFF 0
#define BRIGHTNESS 1
#define COLOR 2

const unsigned char startByte = 55;

typedef struct _controllValues {
    unsigned char hasSeenStartByte;
    unsigned char dataBytesSinceStartByte;
} ControllValues;

class Bluetooth {

private:
    void (*on_off_callback)(unsigned char, unsigned char);
    void (*brightness_callback)(unsigned char, unsigned char);
    void (*color_callback)(RGB, unsigned char);
    unsigned char _data[16];
    unsigned char _numberOfDataRead = 0;
    unsigned char _type;
    unsigned char _onOff;
    unsigned char _brightness;
    unsigned char _checksum;
    RGB _rgbColor;
    ControllValues _controllValues;

public:
    Bluetooth(  void (*on_off)(unsigned char, unsigned char),
                void (*brightness)(unsigned char, unsigned char),
                void (*color)(RGB, unsigned char));

    void addDataByte(unsigned char dataByte);

    void setData(unsigned char dataByteNr, unsigned char data);

    void issueCommand(unsigned char);

    char processData();

};

#endif