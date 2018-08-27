#pragma once

#include <Arduino.h>
#include <list>


class Utils {
public:
  static void SetRandomSeed();
  static bool Tokenize(const String line, std::list<String>& args);
};
