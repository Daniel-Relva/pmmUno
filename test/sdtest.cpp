// Adaptador MicroSD
// Teste de escrita no cartão microSD
// Data: 27/01/21
// Libs: SD

// CS: 8
// DI: 11
// SCK: 13
// DO: 12
// CD: 9

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

File myFile;

void setup()
{
    // Open serial communications and wait for port to open:
    Serial.begin(9600);
    while (!Serial)
    {
        ; // wait for serial port to connect. Needed for native USB port only
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
        for (int i = 0; i < 20; i++)
        {
            myFile.println(i);
        }
        myFile.println("--- Fim ---");
        // close the file:
        myFile.close();
        Serial.println("done.");
    }
    else
    {
        // if the file didn't open, print an error:
        Serial.println("error opening test.txt");
    }
}
void loop()
{
    // nothing happens after setup
}