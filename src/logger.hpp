#pragma once

#include <Arduino.h>

class Logger;
extern Logger *lg;

class Logger {
private:
  static Logger *_instance;
  Logger();

public:
  static Logger *Instance();
  void Print(String message);
  void PrintRaw(String message);
};
