#include <textscroller.hpp>
#include <screen.hpp>
#include <text.hpp>
#include <logger.hpp>
#include <utils.hpp>
#include <Arduino.h>


void TextScroller::Init() {
  red = random(BRIGHTNESS_MIN, BRIGHTNESS_MAX);
  green = random(BRIGHTNESS_MIN, BRIGHTNESS_MAX);
  blue = random(BRIGHTNESS_MIN, BRIGHTNESS_MAX);
  redDirection = -1;
  greenDirection = +1;
  blueDirection = -1;

  maxX = Screen::WIDTH - 1;

  SetText("...");
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

  lg->Print("New text: '" + String(message.c_str()) + "' of size: " + String(length));
}

void TextScroller::ScrollTextColor(ScrollDirection dir) {
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
  RandomizeColor(red, redDirection);
  RandomizeColor(green, greenDirection);
  RandomizeColor(blue, blueDirection);

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

  //lg->PrintOne("Rainbowing: R" + String(red) + " G" + String(green) + " B" + String(blue) + "      \r");
  Display();
}

void TextScroller::RandomizeColor(int8_t &color, int8_t &direction) {
  color += direction * random(0, CHANGE_SPEED);

  if(color <= BRIGHTNESS_MIN) {
    color = BRIGHTNESS_MIN;
    direction = -direction;
  } else if(color >= BRIGHTNESS_MAX) { 
    color = BRIGHTNESS_MAX;
    direction = -direction;
  }
}

void TextScroller::Display() {
  screen->SetAllPixels(Screen::BLACK);
  text->Display(scrollMessage, position, 0, [&](int16_t xP, int16_t yP, bool on) {
    screen->SetPixel(xP, yP, on ? RgbColor(red, green, blue) : Screen::BLACK);
  });

  screen->Show();
  delay(180);
}
