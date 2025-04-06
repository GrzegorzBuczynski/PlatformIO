#pragma once
#include <Arduino.h>

class ImageData
{
public:
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
    const uint16_t *data;

    ImageData(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint16_t *data);
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