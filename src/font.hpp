#pragma once

#include <string>
#include <stdint.h>

class Font {
public:
    static const std::string CHAR_TO_SYMBOL;

    static const uint64_t BITMAPS[];

    static const uint16_t BITMAP_INVALID_CHARACTER;
    static const uint16_t BITMAPS_LEN;

};
