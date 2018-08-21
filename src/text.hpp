#pragma once

#include <Arduino.h>
#include <functional>
#include <stdint.h>

class Text;
extern Text *text;

class Text {
public:
  typedef std::function<void (int8_t x, int8_t y, bool on)> PixelPrinterLambda;

private:
    static const uint8_t FONT_WIDTH = 8;
    static const uint8_t FONT_HEIGHT = 8;

public:
    void Display(std::string text, int16_t x, int16_t y, PixelPrinterLambda operation);
    uint16_t StringLength(std::string text);
    uint16_t StringPixelSize(std::string text);

private:
    void DisplayChar(uint64_t symbol, int16_t xPos, int16_t yPos, PixelPrinterLambda operation);
    uint64_t GetSymbol(uint32_t codepoint);
};
