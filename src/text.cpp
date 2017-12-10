#include <text.hpp>
#include <font.hpp>
#include <screen.hpp>
#include <logger.hpp>
#include <string>

void Text::Display(std::string text, int16_t x, int16_t y, PixelPrinterLambda operation) {
  uint16_t stringOffset = 0;
  uint16_t arrayOffset = 0;
  uint32_t character = 0;

  while (arrayOffset < text.length()) {
    // Find the next character in the given string's bytes
    if (!GetUtf8Character(text, stringOffset, stringOffset, arrayOffset, character)) {
      lg->Print("!!! Cannot read input string.");
      return;
    }
    arrayOffset++;
    DisplayChar(GetSymbolIndex(character), (stringOffset++*FONT_WIDTH) + x, y, operation);
  }
  lg->Print("Displayed: " + String(text.c_str()));
}

uint16_t Text::GetSymbolIndex(uint32_t character) {
  uint16_t arrayOffset = 0;
  uint16_t symbolIndex = 0;
  uint32_t currentChar = 0;

  for (uint16_t pos = 0 ; pos < Font::BITMAPS_LEN ; ++pos) {
    if (!GetUtf8Character(Font::CHAR_TO_SYMBOL, pos, pos, arrayOffset, currentChar)) {
      lg->Print("!!! Cannot read symbol lookup string.");
      return Font::BITMAP_INVALID_CHARACTER;
    }
    if (currentChar == character) {
//      lg->Print("GetSymbolIndex: OK: symbol for [" + lg->PrintHex(character) + "] found at " + String(pos));
      return pos;
    } else {
//      lg->Print("GetSymbolIndex: symbol for [" + lg->PrintHex(character) + "] doesn't match [" + lg->PrintHex(currentChar) + "] at " + String(pos));
    }
    arrayOffset++;
  }

  lg->Print("GetSymbolIndex: FAIL: symbol for [" + lg->PrintHex(character) + "] not found");
  return Font::BITMAP_INVALID_CHARACTER;
}

/**
 * Get which UTF-8 character is at position stringPos
 * This would be unnecessary if arduino supported multibyte strings
 * @param str  The string, duh
 * @param stringPos  The character to get from the string
 * @param stringOffset  Where to start looking from in the string, considering multibyte chars as one
 * @param arrayOffset  Where to start looking from in the array bytes
 *                     Updated with which byte in the array 'stringPos' is located
 * @param character  The multibyte character you were looking for
 * @return bool
 */
bool Text::GetUtf8Character(const std::string& str, const uint16_t stringPos, const uint16_t stringOffset, uint16_t &arrayOffset, uint32_t &character) {
  if (arrayOffset >= str.length()) {
    lg->Print("!!! Invalid array offset past the end of string!");
    return false;
  }

  uint16_t currentStringOffset = stringOffset;
  while (arrayOffset < str.length()) {
    uint8_t ascii = str.at(arrayOffset);
  
    if (ascii < 128) {
      character = ascii;
    } else {
      uint8_t asciiAfter = str.at(arrayOffset + 1);
      switch (ascii) {
        case 0xC2:
        case 0xC3:
          arrayOffset++;
          if (arrayOffset >= str.length()) {
            lg->Print("!!! Broken last character? stringPos " + String(stringPos) + ", code " + String(ascii, 16));
            return false;
          }
          character = (ascii << 8) + asciiAfter;
//          lg->Print("Found 2-byter at stringPos: " + String(stringPos) + " - " + String(ascii, 16) + " " + String(asciiAfter, 16));
          break;
        case 0xE2:
          arrayOffset += 2;
          if (arrayOffset >= str.length()) {
            lg->Print("!!! Broken last character? stringPos " + String(stringPos) + ", code " + String(ascii, 16));
            return false;
          }
          character = (ascii << 16) + (asciiAfter << 8) + (uint8_t)str.at(arrayOffset + 2);
//          lg->Print("Found 3-byter at stringPos: " + String(stringPos) + " - " + String(ascii, 16) + " " + String(asciiAfter, 16) + " " + String(str.at(arrayOffset+2), 16));
          break;
        default:
          lg->Print("!!! Unsupported character at stringPos " + String(stringPos) + " [" + lg->PrintHex(character) + "]");
          return false;
      }
    }
    if (stringPos == currentStringOffset) {
//      lg->Print("GetUtf8Character: Index in string: " + String(currentStringOffset)
//       + " letter " + lg->PrintHex(character)
//       + " char " + String((char)character));
      return true;
    }
    currentStringOffset++;
    arrayOffset++;
  }

  return false;
}

void Text::DisplaySimple(std::string text, int16_t x, int16_t y, PixelPrinterLambda operation) {
  for (int pos = 0 ; pos < text.length() ; ++pos) {
    uint8_t ch = text.at(pos);
    int16_t symbolIndex = Font::CHAR_TO_SYMBOL.find(ch);
    if (symbolIndex == std::string::npos || symbolIndex >= Font::BITMAPS_LEN)
    {
      symbolIndex = Font::BITMAP_INVALID_CHARACTER;
    }
    DisplayChar(symbolIndex, (pos*FONT_WIDTH) + x, y, operation);
  }
}

void Text::DisplayChar(uint16_t symbolIndex, int16_t xPos, int16_t yPos, PixelPrinterLambda operation) {
//    lg->Print("Printing character " + String(symbolIndex) + " at (" + String(xPos) + "," + String(yPos) + ")");
    for (int row = 0 ; row < FONT_HEIGHT ; ++row) {
      uint8_t value = (Font::BITMAPS[symbolIndex] >> row * 8) & 0xFF;
      for (int x = 0 ; x < FONT_WIDTH ; ++x) {
        operation(x + xPos, row + yPos, bitRead(value, x));
      }
    }
}

uint16_t Text::StringPixelSize(std::string string) {
  return string.length() * FONT_WIDTH;
}
