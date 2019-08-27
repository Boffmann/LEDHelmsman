#include "Bluetooth.h"

Bluetooth::Bluetooth(  void (*on_off)(unsigned char, unsigned char),
                void (*brightness)(unsigned char, unsigned char),
                void (*color)(RGB, unsigned char)) {
        on_off_callback = on_off;
        brightness_callback = brightness;
        color_callback = color;

        _checksum = 0;
        _rgbColor = RGB(0, 0, 0);
        _controllValues.hasSeenStartByte = false;
        _controllValues.dataBytesSinceStartByte = 0;
    }

void Bluetooth::addDataByte(unsigned char dataByte) {
        _data[_numberOfDataRead] = dataByte;
        if (_numberOfDataRead < 15)  {
             _numberOfDataRead++;
        }
    }

void Bluetooth::setData(unsigned char dataByteNr, unsigned char data) {
        switch(_type) {
            case ONOFF:
                if (dataByteNr == 1) {
                    _onOff = data;
                }
                break;
            case BRIGHTNESS:
                if (dataByteNr == 1) {
                    _brightness = data;
                }
                break;
            case COLOR:
                switch (dataByteNr) {
                    case 1:
                        _rgbColor.setRed(data);
                        break;
                    case 2: 
                        _rgbColor.setGreen(data);
                        break;
                    case 3:
                        _rgbColor.setBlue(data);
                        break;
                }
                break;
        }
    }

    void Bluetooth::issueCommand(unsigned char processingSuccessful) {
        switch (_type) {
            case ONOFF:
                on_off_callback(_onOff, processingSuccessful);
                break;
            case BRIGHTNESS:
                brightness_callback(_brightness, processingSuccessful);
                break;
            case COLOR:
                color_callback(_rgbColor, processingSuccessful);
                break;
        }
    }

    char Bluetooth::processData() {
        unsigned char isChecksumCorrect = true;

        for (int i = 0; i < (int)_numberOfDataRead; i++) {
            unsigned char currentDataByte = _data[i];
            
            // Wait until first start byte has been seen
            if (!_controllValues.hasSeenStartByte) {
                if (currentDataByte != startByte) {
                    continue;
                } else {
                    _controllValues.hasSeenStartByte = true;
                    _controllValues.dataBytesSinceStartByte = 0;
                }
            }
            switch (_controllValues.dataBytesSinceStartByte) {
                case 1: // Type
                    _type = _data[i];
                    _checksum += _data[i];
                    break;
                case 2: // Data Byte 1
                    setData(1, _data[i]);
                    _checksum += _data[i];
                    break;
                case 3: // Data Byte 2
                    setData(2, _data[i]);
                    _checksum += _data[i];
                    break;
                case 4: // Data Byte 3
                    setData(3, _data[i]);
                    _checksum += _data[i];
                    break;
                case 5: 
                    { // Checksum
                        unsigned char checksum = _data[i];
                        isChecksumCorrect = (checksum == _checksum);
                        _checksum = 0;
                        break;
                    }
                case 6: // Stop Byte
                    _controllValues.hasSeenStartByte = false;
                    issueCommand(isChecksumCorrect);
                    break;
            }
            _controllValues.dataBytesSinceStartByte++;
        }
        _numberOfDataRead = 0;
        return isChecksumCorrect;
    }