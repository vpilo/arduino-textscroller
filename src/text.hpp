#pragma once

#include <Arduino.h>
#include <functional>
#include <stdint.h>

class Text;
extern Text *text;

using coord_t = int16_t;

class Text {
public:
  typedef std::function<void (coord_t x, coord_t y, bool on)> PixelPrinterLambda;

private:
    static const coord_t FONT_WIDTH = 8;
    static const coord_t FONT_HEIGHT = 8;

public:
    void Display(String text, coord_t x, coord_t y, PixelPrinterLambda operation);
    uint16_t StringLength(String text);
    uint16_t StringPixelSize(String text);

private:
    bool DisplayChar(uint64_t symbol, coord_t xPos, coord_t yPos, PixelPrinterLambda operation);
    uint64_t GetSymbol(uint32_t codepoint);
};
