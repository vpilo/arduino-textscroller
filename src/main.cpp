#include <Arduino.h>
#include <screen.hpp>
#include <text.hpp>
#include <logger.hpp>

Screen screen;
Text text;
Logger *lg = Logger::Instance();

void setup() {
  screen.Init();
}

int8_t redDir = +5;
int8_t greenDir = +5;
int8_t blueDir = -5;
int8_t min = 0;
int8_t max = 64;
int16_t red = min;
int16_t green = max;
int16_t blue = (max - min) / 2;

std::string message = "┄ V@l€ríØ :)";
int minX = - text.StringPixelSize(message) + 1;
int maxX = screen.WIDTH - 1;
int x = maxX;

void loop() {
//  lg->PrintOne("R" + String(red) + " G" + String(green) + " B" + String(blue) + "\r");

  text.Display(message, x, 0, [&](int8_t xP, int8_t yP, bool on) {
    screen.SetPixel(xP, yP, on ? RgbColor(red,green,blue) : screen.BLACK);
  });

  screen.Show();
  delay(60);

  red += redDir;
  green += greenDir;
  blue += blueDir;
  if(red <= min || red >= max) { redDir = -redDir; red += redDir; }
  if(green <= min || green >= max) { greenDir = -greenDir; green += greenDir; }
  if(blue <= min || blue >= max) { blueDir = -blueDir; blue += blueDir;}

  x--;
  if (x <= minX) {
    x = maxX;
  }
}
