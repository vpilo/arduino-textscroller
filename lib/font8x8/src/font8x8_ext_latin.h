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
// Contains an 8x8 font map for unicode points U+00A0 - U+00FF (extended latin)
#define FONT8X8_EXT_LATIN_BEGIN  0x00A0
#define FONT8X8_EXT_LATIN_END    0x00FF

uint64_t font8x8_ext_latin[96] = {
    0x0000000000000000,   // U+00A0 (no break space)
    0x0018181818001818,   // U+00A1 (inverted !)
    0x18187E03037E1818,   // U+00A2 (dollarcents)
    0x003F67060F26361C,   // U+00A3 (pound sterling)
    0x00633E363E630000,   // U+00A4 (currency mark)
    0x0C0C3F0C3F1E3333,   // U+00A5 (yen)
    0x0018181800181818,   // U+00A6 (broken pipe)
    0x1E331C36361CC67C,   // U+00A7 (paragraph)
    0x0000000000000033,   // U+00A8 (diaeresis)
    0x3C4299858599423C,   // U+00A9 (copyright symbol)
    0x000000007C36363C,   // U+00AA (superscript a)
    0x0000CC663366CC00,   // U+00AB (<<)
    0x000030303F000000,   // U+00AC (gun pointing left)
    0x0000000000000000,   // U+00AD (soft hyphen)
    0x3C42A59DA59D423C,   // U+00AE (registered symbol)
    0x000000000000007E,   // U+00AF (macron)
    0x000000001C36361C,   // U+00B0 (degree)
    0x007E0018187E1818,   // U+00B1 (plusminus)
    0x0000003C0C18301C,   // U+00B2 (superscript 2)
    0x0000001C3018301C,   // U+00B2 (superscript 3)
    0x0000000000000C18,   // U+00B2 (aigu)
    0x03063E6666660000,   // U+00B5 (mu)
    0x00D8D8D8DEDBDBFE,   // U+00B6 (pilcrow)
    0x0000001818000000,   // U+00B7 (central dot)
    0x1E30180000000000,   // U+00B8 (cedille)
    0x000000001C080C08,   // U+00B9 (superscript 1)
    0x000000001C36361C,   // U+00BA (superscript 0)
    0x00003366CC663300,   // U+00BB (>>)
    0x03F3F6ECBD3363C3,   // U+00BC (1/4)
    0xF03366CC7B3363C3,   // U+00BD (1/2)
    0x80E6ACDBB463C403,   // U+00BE (3/4)
    0x001E3303060C000C,   // U+00BF (inverted ?)
    0x00637F63361C0007,   // U+00C0 (A grave)
    0x00637F63361C0070,   // U+00C1 (A aigu)
    0x00637F633E00361C,   // U+00C2 (A circumflex)
    0x00637F633E003B6E,   // U+00C3 (A ~)
    0x0063637F63361C63,   // U+00C4 (A umlaut)
    0x00333F331E000C0C,   // U+00C5 (A ring)
    0x007333337F33367C,   // U+00C6 (AE)
    0x1E30181E3303331E,   // U+00C7 (C cedille)
    0x003F061E063F0007,   // U+00C8 (E grave)
    0x003F061E063F0038,   // U+00C9 (E aigu)
    0x003F061E063F120C,   // U+00CA (E circumflex)
    0x003F061E063F0036,   // U+00CB (E umlaut)
    0x001E0C0C0C1E0007,   // U+00CC (I grave)
    0x001E0C0C0C1E0038,   // U+00CD (I aigu)
    0x001E0C0C1E00120C,   // U+00CE (I circumflex)
    0x001E0C0C0C1E0033,   // U+00CF (I umlaut)
    0x003F66666F6F663F,   // U+00D0 (Eth)
    0x00333B3F3733003F,   // U+00D1 (N ~)
    0x00183C663C18000E,   // U+00D2 (O grave)
    0x00183C663C180070,   // U+00D3 (O aigu)
    0x00183C663C18663C,   // U+00D4 (O circumflex)
    0x003E63633E003B6E,   // U+00D5 (O ~)
    0x00183C66663C18C3,   // U+00D6 (O umlaut)
    0x0000361C081C3600,   // U+00D7 (multiplicative x)
    0x001D366F7B73365C,   // U+00D8 (O stroke)
    0x003C66666666000E,   // U+00D9 (U grave)
    0x003C666666660070,   // U+00DA (U aigu)
    0x003C66666600663C,   // U+00DB (U circumflex)
    0x001E333333330033,   // U+00DC (U umlaut)
    0x0018183C66660070,   // U+00DD (Y aigu)
    0x0F063E66663E060F,   // U+00DE (Thorn)
    0x03031F331F331E00,   // U+00DF (beta)
    0x007E333E301E0007,   // U+00E0 (a grave)
    0x007E333E301E0038,   // U+00E1 (a aigu)
    0x00FC667C603CC37E,   // U+00E2 (a circumflex)
    0x007E333E301E3B6E,   // U+00E3 (a ~)
    0x007E333E301E0033,   // U+00E4 (a umlaut)
    0x007E333E301E0C0C,   // U+00E5 (a ring)
    0x00FE33FE30FE0000,   // U+00E6 (ae)
    0x1C301E03031E0000,   // U+00E7 (c cedille)
    0x001E033F331E0007,   // U+00E8 (e grave)
    0x001E033F331E0038,   // U+00E9 (e aigu)
    0x003C067E663CC37E,   // U+00EA (e circumflex)
    0x001E033F331E0033,   // U+00EB (e umlaut)
    0x001E0C0C0C0E0007,   // U+00EC (i grave)
    0x001E0C0C0C0E001C,   // U+00ED (i augu)
    0x003C1818181C633E,   // U+00EE (i circumflex)
    0x001E0C0C0C0E0033,   // U+00EF (i umlaut)
    0x001E333E301B0E1B,   // U+00F0 (eth)
    0x003333331F001F00,   // U+00F1 (n ~)
    0x001E33331E000700,   // U+00F2 (o grave)
    0x001E33331E003800,   // U+00F3 (o aigu)
    0x001E33331E00331E,   // U+00F4 (o circumflex)
    0x001E33331E003B6E,   // U+00F5 (o ~)
    0x001E33331E003300,   // U+00F6 (o umlaut)
    0x001818007E001818,   // U+00F7 (division)
    0x063C6E7E763C6000,   // U+00F8 (o stroke)
    0x007E333333000700,   // U+00F9 (u grave)
    0x007E333333003800,   // U+00FA (u aigu)
    0x007E33333300331E,   // U+00FB (u circumflex)
    0x007E333333003300,   // U+00FC (u umlaut)
    0x1F303E3333003800,   // U+00FD (y aigu)
    0x00063E663E060000,   // U+00FE (thorn)
    0x1F303E3333003300    // U+00FF (y umlaut)
};
