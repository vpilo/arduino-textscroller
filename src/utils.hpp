#pragma once

#include <Arduino.h>
#include <list>
#include <vector>


class Utils {
public:
  static void SetRandomSeed();
  static bool Tokenize(const String line, std::list<String>& args);
  static void LogFPS();
  static uint8_t GetHexDigit(const char* ch);

private:
  static uint32_t frames;
  static uint32_t lastFrame;
};
