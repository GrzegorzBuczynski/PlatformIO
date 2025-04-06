#include <Arduino.h>

#include "MyDisplay.hpp"
#include "Panel.hpp"



MyDisplay display; 
// HomePanel homePanel;

void drawImage() {
    int x = 5, y = 0;
    display._tft.setAddrWindow(x, y, x + 64 - 1, y + 64 - 1);
    display._tft.pushColors((const uint8_t*)marilyn_64x64, 64 * 64, 1, false);
    display._tft.setAddrWindow(0, 0, display._tft.width() - 1, display._tft.height() - 1);
}

void setup(void) {
    Serial.begin(9600);
    display.begin();
    Serial.println("Display initialized.");

    // Test bezpośredniego rysowania obrazu
    Serial.println("Testing direct image drawing...");
    drawImage();
    Serial.println("Direct image drawing test complete");
    
    // Teraz spróbuj normalnie
    display.drawPanel(new HomePanel());
}


void idle() {
    delay(100); // Adjust the delay as needed
}

void loop(void)
{
    idle(); // Call the idle function to keep the loop running without blocking
}





// if (display.refresh) {
//     display.refresh = 0; // Reset the refresh flag
//     // display.drawPanel(homePanel); // Draw the panel on the display
// }
// Adafruit_GFX_Button &on_btn = display.on_btn;
// Adafruit_GFX_Button &off_btn = display.off_btn;
// MCUFRIEND_kbv &tft = display.getTft(); // Referencja do obiektu wyświetlacza
// int pixel_x = display.pixel_x;
// int pixel_y = display.pixel_y;

// bool down = display.Touch_getXY();
// on_btn.press(down && on_btn.contains(pixel_x, pixel_y));
// off_btn.press(down && off_btn.contains(pixel_x, pixel_y));
// if (on_btn.justReleased())
//     on_btn.drawButton();
// if (off_btn.justReleased())
//     off_btn.drawButton();
// if (on_btn.justPressed()) {
//     on_btn.drawButton(true);
//     tft.fillRect(40, 80, 160, 80, GREEN);
// }
// if (off_btn.justPressed()) {
//     off_btn.drawButton(true);
//     tft.fillRect(40, 80, 160, 80, RED);
// }
// Serial.println("Display initialized.");