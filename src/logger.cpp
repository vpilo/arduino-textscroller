#include <logger.hpp>
#include <Arduino.h>

Logger *Logger::_instance = { nullptr };

Logger *Logger::Instance() {
  if (_instance == nullptr) {
    _instance = new Logger;
  }
  return _instance;
}

Logger::Logger() {
  Serial.begin(115200);
  while (!Serial); // wait for serial attach

  Print("\n\nHello!");
}

void Logger::Print(String message) {
  Serial.println(message);
  Serial.flush();
}

void Logger::PrintRaw(String message) {
  Serial.print(message);
  Serial.flush();
}
