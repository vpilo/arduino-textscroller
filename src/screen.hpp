#pragma once

#include <NeoPixelBus.h>
#include <stdint.h>
#include <config.h>

class Screen;
extern Screen *screen;

class Screen {
public:
    static const uint16_t PIXELS = SCREEN_WIDTH * SCREEN_HEIGHT;

    // Max brightness for white - lower than for normal colors as
    // the white degrades into other colors (yellow) above this threshold
    static const uint8_t MAX_BRIGHTNESS_WHITE = 63;
    static const uint8_t MAX_BRIGHTNESS_COLORS = 255;
    static const RgbColor WHITE;
    static const RgbColor BLACK;

private:
    const uint16_t _testFrameDuration = 5; // ms

    NeoTopology<ColumnMajorAlternating270Layout> _topo = { SCREEN_WIDTH, SCREEN_HEIGHT };
    NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> _strip = { PIXELS };

public:
    Screen();
    void Test();

    void Clear();

    void ScreenToGray(int brightness);
    void ScreenToColor(RgbColor color);

    // Manual pixel management
    void SetPixel(int8_t x, int8_t y, RgbColor color);
    void SetAllPixels(RgbColor color);
    void Show();
};
