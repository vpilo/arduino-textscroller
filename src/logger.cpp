#include <logger.hpp>
#include <Arduino.h>

Logger *Logger::_instance = { nullptr };

Logger *Logger::Instance() {
  if (_instance == nullptr) {
    _instance = new Logger;
    _instance->Init();
  }
  return _instance;
}

void Logger::Init() {
  Serial.begin(115200);
  while (!Serial); // wait for serial attach
  
  Print("\n\nHello!");
}

void Logger::Print(String message) {
  Serial.println(message);
  Serial.flush();
}

void Logger::PrintOne(String message) {
  Serial.print(message);
  Serial.flush();
}

String Logger::PrintHex(uint32_t value) {
  return String((int)((value>>24)&0xFF), 16) + " " + String((int)((value>>16)&0xFF), 16) +
         String((int)((value>>8)&0xFF), 16) + " " + String((int)((value)&0xFF), 16);
}