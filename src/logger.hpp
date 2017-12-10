#pragma once

#include <Arduino.h>

class Logger;
extern Logger *lg;

class Logger {
private:
  static Logger *_instance;
  void Init();

public:
  static Logger *Instance();
  void Print(String message);
  void PrintOne(String message);
  String PrintHex(uint32_t value);
};
