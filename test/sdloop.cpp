/*
 * This program is a simple Print benchmark.
 */
#include <SPI.h>
#include "SdFat.h"
#include "sdios.h"
#include "FreeStack.h"

// SD chip select pin
const uint8_t chipSelect = 8;

// number of lines to print
const uint16_t N_PRINT = 20000;

// file system
SdFat sd;

// test file
SdFile file;

// Serial output stream
ArduinoOutStream cout(Serial);
//------------------------------------------------------------------------------
// store error strings in flash to save RAM
#define error(s) sd.errorHalt(F(s))
//------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  // Wait for USB Serial 
  while (!Serial) {
    SysCall::yield();
  }
  file.flush();
}
void loop() {
    if (!sd.begin(chipSelect, SD_SCK_MHZ(50))) {
      sd.initErrorHalt();
    }

    long timeStamp = millis();
    String dataString = "Hello There!";
    // Open a file and write to it.
    if (file.open("log.csv", FILE_WRITE)) {
        file.print(timeStamp);
        file.print(",");
        file.println(dataString);
        file.close();  // Data isn't actually written until we
        // close the connection!
        // Print same thing to the screen for debugging
        Serial.print(timeStamp);
        Serial.print(",");
        Serial.println(dataString);
    } else {
        Serial.println("Couldn't open log file");
    }
    delay(500);
}