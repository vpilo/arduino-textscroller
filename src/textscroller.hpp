#pragma once

#include <text.hpp>

#include <NeoPixelBus.h>

// Brightness of each color channel
#define BRIGHTNESS_MIN  0
#define BRIGHTNESS_MAX  48

#define CHANGE_SPEED  3

class TextScroller {
public:
  enum ScrollDirection {
    Left,
    Right
  };
  
public:
  void Init();

  void SetText(const String& message);
  void SetScrollColor(RgbColor color);

  void ScrollTextColor(ScrollDirection dir);
  void ScrollTextRainbow(ScrollDirection dir);

private:
  void Display();
  void RandomizeColor(int8_t &color, int8_t &direction);

private:
  // Colors for rainbow mode
  int8_t red;
  int8_t redDirection;
  int8_t green;
  int8_t greenDirection;
  int8_t blue;
  int8_t blueDirection;

  coord_t minX;
  coord_t maxX;

  coord_t position;
  std::string scrollMessage;
};
