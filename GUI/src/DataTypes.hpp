#pragma once
#include <Arduino.h>

struct ImageData
{
    const uint8_t *data;
    int width;
    int height;
};