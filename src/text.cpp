#include <text.hpp>
#include <screen.hpp>
#include <logger.hpp>
#include <string>
#include "font8x8.h"
#include "utf8.h"

//#define VERBOSE

void Text::Display(String text, coord_t x, coord_t y, PixelPrinterLambda operation) {
  uint32_t codepoint;
  uint32_t state = UTF8_ACCEPT;
  coord_t stringOffset = 0;
  const char *c_str = text.c_str();
  bool displayed;

#ifdef VERBOSE
  lg->Print("Displaying: " + text + " (" + String(x) + "," + String(y) + ")");
#endif

  for (; *c_str; ++c_str) {
    if (!utf8decode(&state, &codepoint, *c_str)) {
      coord_t newX = (stringOffset * FONT_WIDTH) + x;
      displayed = DisplayChar(GetSymbol(codepoint), newX, y, operation);
      stringOffset++;
      if (displayed) {
#ifdef VERBOSE
        lg->Print("Char " + String(*c_str) + " at (" + String((long)newX,10) + "," + String(y) + ")"
//                " hex: " + String((unsigned long)GetSymbol(codepoint), 16)
        );
#endif
      }
    }
  }
}

uint64_t Text::GetSymbol(uint32_t codepoint) {
  if (codepoint >= FONT8X8_BASIC_BEGIN && codepoint <= FONT8X8_BASIC_END) {
    return font8x8_basic[codepoint - FONT8X8_BASIC_BEGIN];
  } else if (codepoint >= FONT8X8_CURRENCIES_BEGIN && codepoint <= FONT8X8_CURRENCIES_END) {
    return font8x8_currencies[codepoint - FONT8X8_CURRENCIES_BEGIN];
  } else if (codepoint >= FONT8X8_EXT_LATIN_BEGIN && codepoint <= FONT8X8_EXT_LATIN_END) {
    return font8x8_ext_latin[codepoint - FONT8X8_EXT_LATIN_BEGIN];
  } else {
#ifdef VERBOSE
    lg->Print("Displaying replacement character for code point: " + String(codepoint, 16));
#endif
    return font8x8_fault[0]; // Invalid character (unknown symbol)
  }
}

bool Text::DisplayChar(uint64_t symbol, coord_t xPos, coord_t yPos, PixelPrinterLambda operation) {
    if (xPos + FONT_WIDTH < 0  ||
        yPos + FONT_HEIGHT < 0 ||
        xPos > Screen::WIDTH   ||
        yPos > Screen::HEIGHT) {
      return false;
    }

    for (coord_t row = 0 ; row < FONT_HEIGHT ; ++row) {
      uint8_t value = (symbol >> row * 8) & 0xFF;
      for (coord_t x = 0 ; x < FONT_WIDTH ; ++x) {
        operation(x + xPos, row + yPos, bitRead(value, x));
      }
    }
    return true;
}

uint16_t Text::StringLength(String text) {
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

uint16_t Text::StringPixelSize(String text) {
  return StringLength(text) * FONT_WIDTH;
}
