#pragma once

#include <Arduino.h>
#include "Colors.hpp"
#include <MCUFRIEND_kbv.h>


struct GBUButton
{
    int x, y, w, h;
    const char *label;
    uint16_t color;
    GBUButton *next; // Dodane pole wskaźnika do następnego elementu
};

typedef struct
{
    GBUButton btnRadio;
    GBUButton btnNavi;
    GBUButton btnParams;
    GBUButton btnCamera;
    GBUButton btnBack;
} ButtonLayout;

void drawButton(GBUButton btn, MCUFRIEND_kbv &tft);
