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
  text = new Text();
  Utils::SetRandomSeed();

  scroll.SetText("This looks like a message!");
}

void loop() {
  scroll.Scroll(true /* rainbow */);
}
