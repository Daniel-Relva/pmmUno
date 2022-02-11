#include <Arduino.h>
class BlinkLed {
    public:
		int led;
		void setLed(int myLed) {
			led = myLed;
		}
		
        void blinkTest() {
            pinMode(led, OUTPUT);
            digitalWrite(led, HIGH);
            delay(1000);             // wait for a second
            digitalWrite(led, LOW);  // turn the LED off by making the voltage LOW
            delay(1000);             // wait for a second
        }

		// void stopBlinking(int ){
		// 	pinMode
		// }
};

void setup() {
}

void loop() {
    BlinkLed test();
	test.setLed(13);
    // test.blinkTest();
}
