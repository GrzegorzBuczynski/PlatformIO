#pragma once
#include <Arduino.h>
#include "GBUButton.hpp"
#include "ScreenParams.hpp"

struct Color1 {
    uint16_t color;
    Color1* next = nullptr;
};

GBUButton *createButtonGrid(uint16_t amount, const char **labels, uint16_t *colors);