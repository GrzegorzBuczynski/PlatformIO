#pragma once
#include <Arduino.h>
#include <Panel.hpp>
#include "MCUFRIEND_kbv.h"
#include "Colors.hpp"
#include <TouchScreen.h>
#include <Adafruit_GFX.h>


#define MINPRESSURE 200
#define MAXPRESSURE 1000

// ALL Touch panels and wiring is DIFFERENT
// copy-paste results from TouchScreen_Calibr_native.ino
const int XP=8,XM=A2,YP=A3,YM=9; //240x400 ID=0x7793
const int TS_LEFT=882,TS_RT=155,TS_TOP=57,TS_BOT=928;

class MyDisplay
{
public:
    Adafruit_GFX_Button on_btn, off_btn;
    MCUFRIEND_kbv _tft;
    void drawImageFromProgmem(int x, int y, int width, int height, const uint16_t* progmemData);

    TouchScreen _ts; // Touchscreen object
    
    uint8_t refresh;
    MyDisplay();
    ~MyDisplay();
    void begin(); // Initialize the display
    uint16_t getID() { return _tft.readID(); } // Get the display ID
    void drawPanel(Panel *_Panel1);
    void drawTemplate();
    // void drawDrawable(Drawable *drawable);
    // void removeDrawable(Drawable *drawable);
    bool Touch_getXY(void);
    int pixel_x, pixel_y; // Touch coordinates
    MCUFRIEND_kbv &getTft() { return _tft; } // Get reference to the display object
};



