#include <screen.hpp>
#include <logger.hpp>

void Screen::Init() {
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
  if (x < 0 || x >= WIDTH) return;
  if (y < 0 || y >= HEIGHT) return;

  _strip.SetPixelColor(_topo.Map(x, y), adjusted);
}

void Screen::Show() {
  _strip.Show();
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
