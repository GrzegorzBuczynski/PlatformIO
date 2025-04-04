#include "MyDisplay.hpp"

MyDisplay::MyDisplay()
    : _ts(XP, YP, XM, YM, 300) // Initialize _ts in the initializer list
{
    uint16_t ID = _tft.readID();
    if (ID == 0xD3D3) ID = 0x9486; // write-only shield
    _tft.begin(ID);
    _tft.setRotation(0); // Set rotation to 0 by default
    _tft.fillScreen(BLACK);
    on_btn.initButton(&_tft,  60, 200, 100, 40, WHITE, CYAN, BLACK, "ON", 2);
    off_btn.initButton(&_tft, 180, 200, 100, 40, WHITE, CYAN, BLACK, "OFF", 2);
    on_btn.drawButton(false);
    off_btn.drawButton(false);
    _tft.fillRect(40, 80, 160, 80, RED);
}

MyDisplay::~MyDisplay()
{
    // Cleanup if needed
}

void MyDisplay::drawPanel(Panel &panel)
{
    MCUFRIEND_kbv &tft = _tft; // Reference to the display object

    tft.setRotation(panel.get_rotation());
    tft.setAddrWindow(0, 0, _width - 1, _height - 1);
    if (panel.hasWallpaper())
        tft.drawRGBBitmap(0, 0, panel.getWallpaper(), 64, 64);
    else
        tft.fillScreen(panel.get_backgroundColor());
    tft.setTextColor(panel.get_foregroundColor());
    tft.setTextSize(2);
    tft.setCursor(0, 0);
    tft.print("Hello, World!");
}

bool MyDisplay::Touch_getXY(void)
{
    MCUFRIEND_kbv &tft = _tft; // Reference to the display object
    TouchScreen ts = _ts; // Reference to the touchscreen object

    TSPoint p = ts.getPoint();
    pinMode(YP, OUTPUT);      //restore shared pins
    pinMode(XM, OUTPUT);
    digitalWrite(YP, HIGH);   //because TFT control pins
    digitalWrite(XM, HIGH);
    bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
    if (pressed) {
        pixel_x = map(p.x, TS_LEFT, TS_RT, 0, tft.width()); //.kbv makes sense to me
        pixel_y = map(p.y, TS_TOP, TS_BOT, 0, tft.height());
    }
    return pressed;
}
