#include <textscroller.hpp>
#include <screen.hpp>
#include <logger.hpp>
#include <utils.hpp>
#include <Arduino.h>
#include <limits.h>


TextScroller::TextScroller() {
  red = random(BRIGHTNESS_MIN, BRIGHTNESS_MAX);
  green = random(BRIGHTNESS_MIN, BRIGHTNESS_MAX);
  blue = random(BRIGHTNESS_MIN, BRIGHTNESS_MAX);
  redDirection = -1;
  greenDirection = +1;
  blueDirection = -1;

  maxX = SCREEN_WIDTH - 1;

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
  if (scrollMessage.compareTo(message) == 0) {
    return;
  }

  scrollMessage = message;

  uint16_t length = text->StringPixelSize(scrollMessage);
  minX = - length + 1;
  position = 0;
  lastDisplay = 0;

  lg->Print("New text - '" + message + "', " + String(length) +
            " px wide (" + String(text->StringLength(scrollMessage)) + " chars)");
}

void TextScroller::Scroll(bool rainbow, ScrollDirection dir) {
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

  if (rainbow) {
    RandomizeColor(red, redDirection);
    RandomizeColor(green, greenDirection);
    RandomizeColor(blue, blueDirection);
  }

  Display();
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
  if (lastDisplay + delay > millis()) {
    return false;
  }
  return true;
}

void TextScroller::Display() {
  lastDisplay = millis();
  screen->SetAllPixels(Screen::BLACK);
  text->Display(scrollMessage, position, 0, [&](coord_t xP, coord_t yP, bool on) {
    screen->SetPixel(xP, yP, on ? RgbColor(red, green, blue) : Screen::BLACK);
  });

  screen->Show();
}
