#include <Adafruit_GFX.h> // Hardware-specific library
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

// work in line numbers.  Font height in ht
int16_t ht = 16, top = 3, line, lines = 15, scroll;
uint8_t i = 0;
void setup()
{
    Serial.begin(9600); // Inicjalizacja portu szeregowego z prędkością 9600 bps
    Serial.println("Serial initialized");

    tft.reset();
    uint16_t id = tft.readID();
    tft.begin(id);
    tft.setRotation(0);     //Portrait
    tft.fillScreen(BLACK);
    tft.setTextColor(WHITE, BLACK);
    tft.setTextSize(2);     // System font is 8 pixels.  ht = 8*2=16
    tft.setCursor(100, 0);
    tft.print("ID = 0x");
    tft.println(id, HEX);
    if (id == 0x9320 || id == 0x9325 || id == 0xB509) {
        top = 0;                      // these controllers scroll full screen
        lines = tft.height() / ht;    // we are in portrait mode
    }
    if (id == 0x7783) {
        tft.println("can NOT scroll");
        while (1);                    // die.
    }
    tft.setCursor(0, 0);
    for (line = 1; line < 21; line++) tft.println(String(line) + ": ");
    
    // Wyczyść dodatkowe 10 wierszy w buforze
    for (int extraLine = lines; extraLine < lines + 10; extraLine++) {
        tft.fillRect(432, 0, tft.width(), ht, BLACK);
    }
}

void loop()
{
    while (i < 27)
    {
        i++;
        tft.vertScroll(0, 432, 16 * i); // Przewijanie całej pamięci
        delay(90);
    }
    Serial.print("offset: "); Serial.println(i * ht);
    i = 0;
    line++;
}
