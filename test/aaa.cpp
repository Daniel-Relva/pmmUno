#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <Wire.h>

#include "Adafruit_BMP3XX.h"

unsigned long currentMillis;
int i;

File myFile;

#define SEALEVELPRESSURE_HPA (1014.25)

Adafruit_BMP3XX bmp;

void setup() {
    // Open serial communications and wait for port to open:
    Serial.begin(9600);
    while (!Serial) {
        ;  // wait for serial port to connect. Needed for native USB port only
    }
    Serial.print("Initializing SD card...");
    if (!SD.begin(8)) {
        Serial.println("initialization failed!");
        while (1)
            ;
    }
    Serial.println("initialization done.");
    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
    if (SD.exists("text.txt")) {
        SD.remove("test.txt");
    }

    myFile = SD.open("test.txt", FILE_WRITE);
    // if the file opened okay, write to it:

    // hardware I2C mode, can pass in address & alt Wire
    if (!bmp.begin_I2C()) {
        Serial.println("Could not find a valid BMP3 sensor, check wiring!");
        while (1)
            ;
    }

    // Set up oversampling and filter initialization
    bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
    bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
    bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
    bmp.setOutputDataRate(BMP3_ODR_50_HZ);

    i = 0;
}
void loop() {
    currentMillis = millis();

    if (!bmp.performReading()) {
        Serial.println("Failed to perform reading :(");
        return;
    }

    if (myFile) {
        myFile.print("Rodada: ");
        myFile.println(i);

        myFile.print("Temperature = ");
        myFile.print(bmp.temperature);
        myFile.println(" *C");

        myFile.print("Pressure = ");
        myFile.print(bmp.pressure / 100.0);
        myFile.println(" hPa");

        myFile.print("Approx. Altitude = ");
        myFile.print(bmp.readAltitude(SEALEVELPRESSURE_HPA));
        myFile.println(" m");

        myFile.println("----------");

        Serial.println(i);
        i++;

        delay(1000);
    }

    if (currentMillis / 1000 > 10) {
        Serial.println("final: " + i);
        myFile.close();
        Serial.println("done.");
    }
}