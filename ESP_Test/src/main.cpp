#include <Arduino_GFX_Library.h>

#define TFT_BL 2  // GPIO for backlight control

// RGB Panel bus setup (24-bit parallel)
Arduino_ESP32RGBPanel *bus = new Arduino_ESP32RGBPanel(
    GFX_NOT_DEFINED, GFX_NOT_DEFINED, GFX_NOT_DEFINED,
    40, // pclk
    41, 39, 42, 45, 48, // r0-r4
    47, 21, 14, 17, 18, 19, // g0-g5
    5, 6, 7, 15, 16, // b0-b4
    0, 8, 4, 8, // hsync
    0, 8, 4, 8, // vsync
    1, 10000000, false // pclk_active_neg, prefer_speed, useBigEndian
);

// Display class
Arduino_RGB_Display *gfx = new Arduino_RGB_Display(
    800, 480, bus, 0, true // width, height, bus, rotation, auto_flush
);

void setup()
{
    gfx->begin();
    gfx->fillScreen(BLACK);

    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);

    gfx->setCursor(10, 10);
    gfx->setTextColor(RED);
    gfx->setTextSize(2);
    gfx->println("Hello World!");
    delay(5000);
}

void loop()
{
    gfx->setCursor(random(gfx->width()), random(gfx->height()));
    gfx->setTextColor(random(0xFFFF), random(0xFFFF));
    gfx->setTextSize(random(1, 5), random(1, 5), random(2));
    gfx->println("Hello World!");
    delay(2000);
}