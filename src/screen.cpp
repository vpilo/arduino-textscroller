#include <screen.hpp>
#include <logger.hpp>

const RgbColor Screen::WHITE = { MAX_BRIGHTNESS_WHITE };
const RgbColor Screen::BLACK = { 0 };


Screen::Screen() {
  _strip.Begin();
  Test();
  Clear();
}

void Screen::SetPixel(int8_t x, int8_t y, RgbColor color) {
  RgbColor adjusted = color;
  if (color.R == color.G && color.G == color.B) {
    adjusted.R = adjusted.G = adjusted.B =
      color.R * MAX_BRIGHTNESS_WHITE / MAX_BRIGHTNESS_COLORS;
  }
  if (x < 0 || x >= SCREEN_WIDTH) return;
  if (y < 0 || y >= SCREEN_HEIGHT) return;

  _strip.SetPixelColor(_topo.Map(x, y), adjusted);
}

void Screen::SetAllPixels(RgbColor color) {
  _strip.ClearTo(color);
}

void Screen::Show() {
  _strip.Show();
}

bool Screen::SetAllPixels(uint32_t* data, uint16_t count) {
  RgbColor color;
  uint16_t current = 0;

  if (count > PIXELS) {
    lg->Print("Expected " + String(PIXELS) + " pixels, got " + String(count));
    return false;
  }

  _strip.ClearTo(BLACK);

  for (int8_t y = 0 ; y < SCREEN_HEIGHT ; ++y) {
    for (int8_t x = 0 ; x < SCREEN_WIDTH ; ++x) {
      uint32_t pixel = data[current++];
      color.R = pixel >> 16;
      color.G = pixel >> 8 & 0xFF;
      color.B = pixel & 0xFF;

      _strip.SetPixelColor(_topo.Map(x, y), color);
      if (current > count) {
        return false;
      }
    }
  }

  _strip.Show();
  return true;
}

void Screen::ScreenToGray(int brightness) {
  RgbColor gray(brightness % MAX_BRIGHTNESS_WHITE);
  _strip.ClearTo(gray);
  _strip.Show();
}

void Screen::ScreenToColor(RgbColor color) {
  RgbColor adjusted = color;
  if (color.R == color.G && color.G == color.B) {
    adjusted.R = adjusted.G = adjusted.B =
      color.R % MAX_BRIGHTNESS_WHITE;
  }
  _strip.ClearTo(adjusted);
  _strip.Show();
}

void Screen::Clear() {
  _strip.ClearTo(BLACK);
  _strip.Show();
}

void Screen::Test() {
  uint8_t frame;

  for (frame = 0 ; frame < MAX_BRIGHTNESS_WHITE ; frame ++) {
    ScreenToGray(frame);
    delay(_testFrameDuration);
  }
  for (frame = MAX_BRIGHTNESS_WHITE ; frame > 0 ; frame --) {
    ScreenToGray(frame);
    delay(_testFrameDuration);
  }
}
