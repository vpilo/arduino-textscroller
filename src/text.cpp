#include <text.hpp>
#include <screen.hpp>
#include <logger.hpp>
#include <string>
#include "font8x8.h"
#include "utf8.h"

void Text::Display(std::string text, int16_t x, int16_t y, PixelPrinterLambda operation) {
  uint32_t codepoint;
  uint32_t state = UTF8_ACCEPT;
  uint16_t stringOffset = 0;
  const char *c_str = text.c_str();

  for (; *c_str; ++c_str) {
    if (!utf8decode(&state, &codepoint, *c_str)) {
      DisplayChar(GetSymbol(codepoint), (stringOffset++*FONT_WIDTH) + x, y, operation);
    }
  }
//  lg->Print("Displayed: " + String(text.c_str()));
}

uint64_t Text::GetSymbol(uint32_t codepoint) {
  if (codepoint >= FONT8X8_BASIC_BEGIN && codepoint <= FONT8X8_BASIC_END) {
    return font8x8_basic[codepoint - FONT8X8_BASIC_BEGIN];
  } else if (codepoint >= FONT8X8_CURRENCIES_BEGIN && codepoint <= FONT8X8_CURRENCIES_END) {
    return font8x8_currencies[codepoint - FONT8X8_CURRENCIES_BEGIN];
  } else if (codepoint >= FONT8X8_EXT_LATIN_BEGIN && codepoint <= FONT8X8_EXT_LATIN_END) {
    return font8x8_ext_latin[codepoint - FONT8X8_EXT_LATIN_BEGIN];
  } else {
//    lg->Print("Displaying replacement character for code point: " + String(codepoint, 16));
    return font8x8_fault[0]; // Invalid character (unknown symbol)
  }
}

void Text::DisplayChar(uint64_t symbol, int16_t xPos, int16_t yPos, PixelPrinterLambda operation) {
//    lg->Print("Printing character " + String((unsigned long)symbol, 16) + " at (" + String(xPos) + "," + String(yPos) + ")");
    for (int row = 0 ; row < FONT_HEIGHT ; ++row) {
      uint8_t value = (symbol >> row * 8) & 0xFF;
      for (int x = 0 ; x < FONT_WIDTH ; ++x) {
        operation(x + xPos, row + yPos, bitRead(value, x));
      }
    }
}

uint16_t Text::StringLength(std::string text) {
  uint32_t codepoint;
  uint32_t state = UTF8_ACCEPT;
  uint16_t length = 0;
  const char *c_str = text.c_str();

  for (; *c_str; ++c_str) {
    if (!utf8decode(&state, &codepoint, *c_str)) {
      length++;
    }
  }
  return length;
}

uint16_t Text::StringPixelSize(std::string text) {
  return StringLength(text) * FONT_WIDTH;
}
