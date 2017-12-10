#pragma once

#include <Arduino.h>
#include <functional>
#include <stdint.h>

class Text {
public:
  typedef std::function<void (int8_t x, int8_t y, bool on)> PixelPrinterLambda;

private:
    static const uint8_t FONT_WIDTH = 8;
    static const uint8_t FONT_HEIGHT = 8;

public:
    void Display(std::string text, int16_t x, int16_t y, PixelPrinterLambda operation);
    void DisplaySimple(std::string text, int16_t x, int16_t y, PixelPrinterLambda operation);
    uint16_t StringPixelSize(std::string string);

private:
    void DisplayChar(uint16_t symbolIndex, int16_t xPos, int16_t yPos, PixelPrinterLambda operation);
    bool GetUtf8Character(const std::string& str, const uint16_t stringPos, uint16_t &stringOffset, uint16_t &arrayOffset, uint32_t &character);
    uint16_t GetSymbolIndex(uint32_t character);
};
