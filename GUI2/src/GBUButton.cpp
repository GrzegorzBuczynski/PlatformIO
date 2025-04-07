#include "GBUButton.hpp"
#include <MCUFRIEND_kbv.h>

void drawButton(GBUButton btn, MCUFRIEND_kbv &tft)
{
    tft.fillRect(btn.x, btn.y, btn.w, btn.h, btn.color);
    tft.setCursor(btn.x + 5, btn.y + 5);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.print(btn.label);
}