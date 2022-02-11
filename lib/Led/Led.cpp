#include <Arduino.h>
#include <Led.h>

void Led::setLedPin(byte myLedPin) {
    this->ledPin = myLedPin;
    pinMode(this->ledPin, OUTPUT);
}

void Led::getLedPin() {
    Serial.println(ledPin);
}

void Led::ledOn() {
    digitalWrite(this->ledPin, HIGH);
}

void Led::ledOff() {
    digitalWrite(this->ledPin, LOW);
}
		
void Led::blink() {
    currentTime = millis();

    if (currentTime - previousTime >= interval) {
        previousTime = currentTime;
        if (!getLedStatus()) {
            setLedStatus(1);
        } else {
            setLedStatus(0);
        }
    }

    digitalWrite(this->ledPin, getLedStatus());
}

int Led::getLedStatus() {
    return this->status;
}

void Led::setLedStatus(int newStatus) {
    this->status = newStatus;
}