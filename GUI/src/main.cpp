#include <Arduino.h>

#include "MyDisplay.hpp"
#include "Panel.hpp"
// #include "MyOS.hpp"

MyDisplay display; 


void setup(void)
{
    Serial.begin(9600);
    display.begin(); // Dynamiczna alokacja obiektu
    Serial.println("Display initialized.");
}


void idle() {
    delay(100); // Adjust the delay as needed
}

void loop(void)
{
    Adafruit_GFX_Button &on_btn = display.on_btn;
    Adafruit_GFX_Button &off_btn = display.off_btn;
    MCUFRIEND_kbv &tft = display.getTft(); // Referencja do obiektu wyświetlacza
    int pixel_x = display.pixel_x;
    int pixel_y = display.pixel_y;

    bool down = display.Touch_getXY();
    on_btn.press(down && on_btn.contains(pixel_x, pixel_y));
    off_btn.press(down && off_btn.contains(pixel_x, pixel_y));
    if (on_btn.justReleased())
        on_btn.drawButton();
    if (off_btn.justReleased())
        off_btn.drawButton();
    if (on_btn.justPressed()) {
        on_btn.drawButton(true);
        tft.fillRect(40, 80, 160, 80, GREEN);
    }
    if (off_btn.justPressed()) {
        off_btn.drawButton(true);
        tft.fillRect(40, 80, 160, 80, RED);
    }
}




