#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BMP3XX.h"

File myFile;

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BMP3XX bmp;

void setup() {
  // Open serial communications and wait for port to open:
    Serial.begin(9600);
    while (!Serial)
    {
        Serial.println("Adafruit BMP388 / BMP390 test");
        ; // wait for serial port to connect. Needed for native USB port only
    }


     if (!bmp.begin_I2C()) // hardware I2C mode, can pass in address & alt Wire
    { 
        Serial.println("Could not find a valid BMP3 sensor, check wiring!");
        while (1);
    }

    Serial.print("Initializing SD card...");
    if (!SD.begin(8))
    {
        Serial.println("initialization failed!");
        while (1)
            ;
    }
 Serial.println("initialization done.");
    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
    myFile = SD.open("test.txt", FILE_WRITE);
    // if the file opened okay, write to it:
    if (myFile)
    {
        Serial.print("Writing to test.txt...");
        myFile.println("--- Inicio ---");
        myFile.println("Data: 27/01/21");
        myFile.println("Autor: Minerva Rockets");
        myFile.println("Esse é um teste da escrita no cartão microSD");
        
        // close the file:
        myFile.close();
        Serial.println("done.");
    }
    else
    {
        // if the file didn't open, print an error:
        Serial.println("error opening test.txt");
    }

    bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
    bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
    bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
    bmp.setOutputDataRate(BMP3_ODR_50_HZ);
}
void loop() {
     myFile = SD.open("bmp.txt", FILE_WRITE);

 myFile = SD.open("test.txt", FILE_WRITE);
    // if the file opened okay, write to it:
    if (myFile)
    {
        if (!bmp.performReading())
    {
        Serial.println("Failed to perform reading :(");
        return;
    }
    myFile.print("Temperature = ");
    myFile.print(bmp.temperature);
     myFile.println(" *C");

     myFile.print("Pressure = ");
     myFile.print(bmp.pressure / 100.0);
     myFile.println(" hPa");

     myFile.print("Approx. Altitude = ");
    myFile.print(bmp.readAltitude(SEALEVELPRESSURE_HPA));
     myFile.println(" m");

     myFile.println();
    
        Serial.print("Writing to test.txt...");

        
        // close the file:
        myFile.close();
        Serial.println("done.");
    }
    else
    {
        // if the file didn't open, print an error:
        Serial.println("error opening test.txt");
    }

    delay(2000);
}