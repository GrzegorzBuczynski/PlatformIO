#pragma once
#include <Arduino.h>

struct ImageData
{
    const uint8_t *data;
    int width;
    int height;
};

struct TextSprite
{
public:
    String *text;
    uint16_t x;
    uint16_t y;
    uint16_t color;
    uint16_t bgColor;
    int fontSize;

    TextSprite();
    TextSprite(String *text, uint16_t x, uint16_t y,  uint16_t color, uint16_t bgColor, uint16_t fontSize);
    ~TextSprite();
};