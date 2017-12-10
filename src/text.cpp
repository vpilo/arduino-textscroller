#include <text.hpp>
#include <font.hpp>
#include <screen.hpp>
#include <logger.hpp>
#include <string>

void Text::Display(std::string text, int16_t x, int16_t y, PixelPrinterLambda operation) {

  uint16_t stringOffset = 0;
  uint16_t arrayOffset = 0;
  uint16_t symbolIndex = 0;
  uint32_t character = 0;

  while (arrayOffset <= text.length()) {
    // Find the next character in the given string's bytes
    if (!FindInString(text, stringOffset, arrayOffset, character)) {
      lg->Print("!!! Cannot read input string.");
      return;
    }
    lg->Print("--> Input now at pos " + String(stringOffset) + ": char " + String((char)character) + " (byte " + String(arrayOffset) + ")");

    delay(100);
#if 0
    if (!FindInString(...)) {
      symbolIndex = Font::SYMBOLS_LEN - 1;
    } else {
      symbolIndex = Font::CHAR_TO_SYMBOL.indexOf(arrayPos);
    }
    DisplayChar(symbolIndex, stringOffset, operation);
#endif
  }

}

/**
 * Find which UTF-8 character is at position stringPos
 * This would be unnecessary if arduino supported multibyte strings
 * @param str  The string, duh
 * @param stringOffset  Where to start looking from in the string, considering multibyte chars as one
 *                      Updated with which position to look for, considering multibyte chars as one
 * @param arrayOffset  Where to start looking from in the array bytes
 *                     Updated with which byte in the array 'stringOffset' is located
 * @param character  The multibyte character you were looking for
 * @return bool
 */
bool Text::FindInString(const std::string& str, const uint16_t stringOffset, uint16_t &arrayOffset, uint32_t &character) {
  //vale®io
  //v a l e \95 \106 i o
  //ABCDEFGHIJKLMNOPQRSTUVWX€asdfgh®jkl
  uint16_t currentStringOffset = stringOffset;

  // Find which actual utf8 character is at 'stringPos' index
  for (; arrayOffset < str.length(); arrayOffset++, currentStringOffset++) {
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
            lg->Print("!!! Broken last character? stringPos " + String(currentStringOffset) + ", code " + String(ascii, 16));
            return false;
          }
          character = (ascii << 8) + asciiAfter;
//          lg->Print("Found 2-byter at stringPos: " + String(currentStringOffset) + " - " + String(ascii, 16) + " " + String(asciiAfter, 16));
          break;
        case 0x82:
          arrayOffset += 2;
          if (arrayOffset >= str.length()) {
            lg->Print("!!! Broken last character? stringPos " + String(currentStringOffset) + ", code " + String(ascii, 16));
            return false;
          }
          character = (ascii << 16) + (asciiAfter << 8) + str.at(arrayOffset + 2);
//          lg->Print("Found 3-byter at stringPos: " + String(currentStringOffset) + " - " + String(ascii, 16) + " " + String(asciiAfter, 16) + " " + String(str.at(arrayOffset+2), 16));
          break;
        default:
          lg->Print("Unsupported character at stringPos " + String(currentStringOffset) + ", code " + String(ascii, 16));
          return false;
      }
    }
    lg->Print("Index in string: " + String(currentStringOffset) + " at arrayPos: " + String(arrayOffset) + " char: " + String(std::string(((char*)&character)+1, 4).c_str()));

    if (stringOffset >= currentStringOffset) {
      lg->Print("Index in string: " + String(currentStringOffset) + " at arrayPos: " + String(arrayOffset) + " char: " + String(std::string(((char*)&character)+1, 4).c_str()));
      return true;
    }
  }

  return true;
}

void Text::DisplaySimple(std::string text, int16_t x, int16_t y, PixelPrinterLambda operation) {
  for (int pos = 0 ; pos < text.length() ; ++pos) {
    uint8_t ch = text.at(pos);
    int16_t symbolIndex = Font::CHAR_TO_SYMBOL.indexOf(ch);
    if (symbolIndex == -1 || symbolIndex >= Font::SYMBOLS_LEN)
    {
      symbolIndex = Font::SYMBOLS_LEN - 1;
    }
    DisplayChar(symbolIndex, (pos*FONT_WIDTH) + x, y, operation);
  }
}

void Text::DisplayChar(uint16_t symbolIndex, int16_t xPos, int16_t yPos, PixelPrinterLambda operation) {
//    lg->Print("Printing character " + String(symbolIndex) + " at (" + String(xPos) + "," + String(yPos) + ")");
    for (int row = 0 ; row < FONT_HEIGHT ; ++row) {
      uint8_t value = (Font::SYMBOLS[symbolIndex] >> row * 8) & 0xFF;
      for (int x = 0 ; x < FONT_WIDTH ; ++x) {
        operation(x + xPos, row + yPos, bitRead(value, x));
      }
    }
}

uint16_t Text::StringPixelSize(std::string string) {
  return string.length() * FONT_WIDTH;
}
