#include <AdafruitSd.h>

bool AdafruitSd::init() {
    if (!begin(SD_ADAFRUIT_CS, SD_SCK_MHZ(SD_ADAFRUIT_SPI_FREQ))) {
        initErrorHalt();
        return false;
    } else {
        Log::printSysln("SD", "Success");
        return true;
    }
}

void AdafruitSd::createFile(const char* filename) {
    FatFile::open(filename, FILE_WRITE);
    closeFile();
}

void AdafruitSd::openFile(const char* filename) {
    FatFile::open(filename, FILE_WRITE);
}

void AdafruitSd::closeFile() {
    SdFile::close();
}

void AdafruitSd::deleteFile(const char* filepath) {
    SdFat::remove(filepath);
}

void AdafruitSd::overwriteFile(const char* filename) {
    if (!fileExists(filename)) {
        createFile(filename);
    } else {
        deleteFile(filename);
        createFile(filename);
    }
}

void AdafruitSd::writeString(const String &text) {
    println(text);
}

void AdafruitSd::writeInt(int num, int base=10) {
    println(num);
}

bool AdafruitSd::fileExists(const char* filename) {
    return SdFat::exists(filename);
}