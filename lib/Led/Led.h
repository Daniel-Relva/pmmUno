#ifndef Led_h
#define Led_h
#include <Arduino.h>

class Led {
    private:
        byte ledPin;
        bool status = 0;
        unsigned long currentTime;
        unsigned long previousTime;
        const unsigned long interval = 100;
    public:
        void setLedPin(byte myLedPin);
        void getLedPin();
        void ledOn();
        void ledOff();
        void blink();
        void setLedStatus(int status);
        int getLedStatus();
};

#endif