#ifndef Log_h
#define Log_h
#include <Arduino.h>

class Log {
    public:
    static void print(String message);
    static void println(String message);
    static void space();
    static void printSys(String system, String message);
    static void printSysln(String system, String message);
    static void printErr(String system, String message);
    static void printErr(String system, int value);
    static void printErrln(String system, String message);
    static void printWar(String system, String message);
    static void printWarln(String system, String message);
};


#endif