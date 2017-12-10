#include <textscroller.hpp>
#include <screen.hpp>
#include <text.hpp>
#include <logger.hpp>
#include <utils.hpp>
#include <Arduino.h>


void TextScroller::Init(std::string message) {
  red = random(BRIGHTNESS_MIN, BRIGHTNESS_MAX);
  green = random(BRIGHTNESS_MIN, BRIGHTNESS_MAX);
  blue = random(BRIGHTNESS_MIN, BRIGHTNESS_MAX);
  redDirection = -1;
  greenDirection = +1;
  blueDirection = -1;

  scrollMessage = message;

  minX = - text->StringPixelSize(message) + 1;
  maxX = Screen::WIDTH - 1;
  position = 0;
}

void TextScroller::ScrollTextColor(ScrollDirection dir, RgbColor color) {
}

void TextScroller::ScrollTextRainbow(ScrollDirection dir) {
  RedirectColor(red, redDirection);
  RedirectColor(green, greenDirection);
  RedirectColor(blue, blueDirection);

  if (dir == Left) {
    position--;
    if (position <= minX) {
      position = maxX;
    }
  } else {
    position++;
    if (position >= maxX) {
      position = minX;
    }
  }

  lg->PrintOne("Rainbowing: R" + String(red) + " G" + String(green) + " B" + String(blue) + "      \r");

  screen->SetAllPixels(Screen::BLACK);
  text->Display(scrollMessage, position, 0, [&](int8_t xP, int8_t yP, bool on) {
    screen->SetPixel(xP, yP, on ? RgbColor(red, green, blue) : Screen::BLACK);
  });

  screen->Show();
  delay(60);
}

void TextScroller::RedirectColor(int8_t &color, int8_t &direction) {
  color += direction * random(0, CHANGE_SPEED);

  if(color <= BRIGHTNESS_MIN) {
    color = BRIGHTNESS_MIN;
    direction = -direction;
  } else if(color >= BRIGHTNESS_MAX) { 
    color = BRIGHTNESS_MAX;
    direction = -direction;
  }
}
