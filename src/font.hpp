#pragma once

#include <stdint.h>

class Font {
public:
    static const String CHAR_TO_SYMBOL;

    static const uint64_t SYMBOLS[] PROGMEM;

    static const uint16_t SYMBOL_INVALID_CHARACTER;
    static const uint16_t SYMBOLS_LEN;

};
