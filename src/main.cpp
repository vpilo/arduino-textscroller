#include <Arduino.h>
#include <screen.hpp>
#include <text.hpp>
#include <logger.hpp>
#include <utils.hpp>

#include <textscroller.hpp>

Screen *screen;
Text *text;
Logger *lg = Logger::Instance();

TextScroller scroll;

void setup() {
  screen = new Screen();
  screen->Init();
  text = new Text();
  Utils::SetRandomSeed();

  scroll.Init("V@l€ríØ┄");
}

void loop() {
  scroll.ScrollTextRainbow(TextScroller::Left);
}
