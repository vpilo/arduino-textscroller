/**
 * 8x8 monochrome bitmap fonts for rendering
 * Author: Daniel Hepper <daniel@hepper.net>
 *
 * License: Public Domain
 *
 * Based on:
 * // Summary: font8x8.h
 * // 8x8 monochrome bitmap fonts for rendering
 * //
 * // Author:
 * //     Marcel Sondaar
 * //     International Business Machines (public domain VGA fonts)
 * //
 * // License:
 * //     Public Domain
 *
 * Fetched from: http://dimensionalrift.homelinux.net/combuster/mos3/?p=viewsource&file=/modules/gfx/font8_8.asm
 **/

// Constant: font8x8_00A0
// Contains an 8x8 font map for unicode points U+20A0 - U+20AF (currencies)
#define FONT8X8_CURRENCIES_BEGIN  0x20AC
#define FONT8X8_CURRENCIES_END    0x20AC

uint64_t font8x8_currencies[1] = {
    0x3C461F061F463C00,   // U+20AC (Euro)
};
