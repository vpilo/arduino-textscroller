#pragma once

#include <NeoPixelBus.h>
#include <stdint.h>

class Screen {
public:
    static const uint16_t WIDTH = 15;
    static const uint16_t HEIGHT = 8;
    static const uint16_t PIXELS = WIDTH * HEIGHT;

    // Max brightness for white - lower than for normal colors as
    // the white degrades into other colors (yellow) above this threshold
    const uint8_t MAX_BRIGHTNESS_WHITE = 63;
    const uint8_t MAX_BRIGHTNESS_COLORS = 255;
    const RgbColor WHITE = { MAX_BRIGHTNESS_WHITE };
    const RgbColor BLACK = { 0 };

private:
    const uint16_t _testFrameDuration = 5; // ms

    NeoTopology<ColumnMajorAlternating270Layout> _topo = { WIDTH, HEIGHT };
    NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> _strip = { PIXELS };

public:
    void Init();


    void Clear();
    void Test();

    void ScreenToGray(int brightness);
    void ScreenToColor(RgbColor color);

    void SetPixel(int8_t x, int8_t y, RgbColor color);
    void Show();
};
