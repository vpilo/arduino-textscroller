#include <textscroller.hpp>
#include <screen.hpp>
#include <logger.hpp>
#include <utils.hpp>
#include <Arduino.h>
#include <limits.h>


void TextScroller::Init() {
  red = random(BRIGHTNESS_MIN, BRIGHTNESS_MAX);
  green = random(BRIGHTNESS_MIN, BRIGHTNESS_MAX);
  blue = random(BRIGHTNESS_MIN, BRIGHTNESS_MAX);
  redDirection = -1;
  greenDirection = +1;
  blueDirection = -1;

  maxX = Screen::WIDTH - 1;

  SetSpeed(DEFAULT_SCROLL_SPEED);
  SetText("...");
}

void TextScroller::SetSpeed(uint16_t speed) {
  if (speed < 1)
    speed = 1;
  if (speed > 10)
    speed = 10;

  delay = 60 * speed;
}

void TextScroller::SetScrollColor(RgbColor color) {
  red = color.R;
  green = color.G;
  blue = color.B;
}

void TextScroller::SetText(const String& message) {
  if (scrollMessage.compare(message.c_str()) == 0) {
    return;
  }

  scrollMessage = message.c_str();

  uint16_t length = text->StringPixelSize(scrollMessage);
  minX = - length + 1;
  position = 0;
  lastDisplay = 0;

  lg->Print("New text - '" + String(message.c_str()) + "', " + String(length) +
            " px wide (" + String(text->StringLength(scrollMessage)) + " chars)");
}

void TextScroller::ScrollTextColor(ScrollDirection dir) {
  if (!CanRender()) {
    return;
  }

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

  Display();
}

void TextScroller::ScrollTextRainbow(ScrollDirection dir) {
  if (!CanRender()) {
    return;
  }

  RandomizeColor(red, redDirection);
  RandomizeColor(green, greenDirection);
  RandomizeColor(blue, blueDirection);

  ScrollTextColor(dir);
}

void TextScroller::RandomizeColor(int8_t &color, int8_t &direction) {
  color += direction * random(0, COLOR_CHANGE_SPEED);

  if(color <= BRIGHTNESS_MIN) {
    color = BRIGHTNESS_MIN;
    direction = -direction;
  } else if(color >= BRIGHTNESS_MAX) { 
    color = BRIGHTNESS_MAX;
    direction = -direction;
  }
}

bool TextScroller::CanRender() {
  uint32_t now = millis();
  if (lastDisplay + delay > now) {
    return false;
  }
  lastDisplay = now;
  return true;
}

void TextScroller::Display() {
  screen->SetAllPixels(Screen::BLACK);
  text->Display(scrollMessage, position, 0, [&](coord_t xP, coord_t yP, bool on) {
    screen->SetPixel(xP, yP, on ? RgbColor(red, green, blue) : Screen::BLACK);
  });

  screen->Show();
}
