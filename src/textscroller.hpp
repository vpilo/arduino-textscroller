#pragma once

#include <text.hpp>

#include <NeoPixelBus.h>

// Brightness of each color channel
#define BRIGHTNESS_MIN  0
#define BRIGHTNESS_MAX  48

#define DEFAULT_SCROLL_SPEED 5

#define COLOR_CHANGE_SPEED  3

class TextScroller {
public:
  enum ScrollDirection {
    Left,
    Right
  };
  
public:
  void Init();

  // 1-10 where 1 is super slow, 10 is crazy fast
  void SetSpeed(uint16_t speed);

  void SetText(const String& message);
  void SetScrollColor(RgbColor color);

  void ScrollTextColor(ScrollDirection dir);
  void ScrollTextRainbow(ScrollDirection dir);

private:
  void Display();
  void RandomizeColor(int8_t &color, int8_t &direction);
  bool CanRender();

private:
  // Colors for rainbow mode
  int8_t red;
  int8_t redDirection;
  int8_t green;
  int8_t greenDirection;
  int8_t blue;
  int8_t blueDirection;

  uint16_t delay;
  uint32_t lastDisplay;

  coord_t minX;
  coord_t maxX;

  coord_t position;
  std::string scrollMessage;
};
