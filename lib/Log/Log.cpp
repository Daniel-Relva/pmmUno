#include <Arduino.h>
#include <Log.h>

void Log::print(String message) {
    Serial.print(message);
}

void Log::println(String message) {
    Serial.println(message);
}

void Log::space() {
    Serial.println(" ");
}

void Log::printSys(String system, String message) {
    Serial.print("[" + system + "]" + " " + message);
}

void Log::printSysln(String system, String message) {
    Serial.println("[" + system + "]" + " " + message);
}

void Log::printErr(String system, String message) {
    Serial.print("[" + system + "]" + "[ERROR] " + message);
}

void Log::printErr(String system, int value) {
    Serial.print("[" + system + "]" + "[ERROR] " + value);
}

void Log::printErrln(String system, String message) {
    Serial.println("[" + system + "]" + "[ERROR] " + message);
}

void Log::printWar(String system, String message) {
    Serial.print("[" + system + "]" + "[WARNING] " + message);
}

void Log::printWarln(String system, String message) {
    Serial.println("[" + system + "]" + "[WARNING] " + message);
}