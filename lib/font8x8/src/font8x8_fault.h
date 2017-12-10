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
// Contains an 8x8 font map for unicode points U+FFFD - U+FFFD (replacement characters)
#define FONT8X8_FAULT_BEGIN  0xFFFD
#define FONT8X8_FAULT_END    0xFFFD

uint64_t font8x8_fault[1] = {
    0x182C7EEFDB663C18,   // U+FFFD (Replacement character)
};
