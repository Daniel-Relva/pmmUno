#ifndef AdafruitSd_h
#define AdafruitSd_h
#include <Arduino.h>
#include <Constants.h>
#include <Log.h>
#include <SPI.h>
#include <SdFat.h>

// CS: 8
// DI: 11
// SCK: 13
// DO: 12
// CD: 9

class AdafruitSd: public SdFat, SdFile {
private:

public:
    bool init();

    void createFile(const char* filename);
    void openFile(const char* filename);
    void closeFile();
    void deleteFile(const char* filepath);
    void overwriteFile(const char* filename);

    void writeString(const String &text);
    void writeInt(int num, int base=10);
    bool fileExists(const char* filename);

    void createDirectory();
    void openDirectory();
    void closeDirectory();
    void deleteDirectory();

    bool isCardConnected();
};

#endif