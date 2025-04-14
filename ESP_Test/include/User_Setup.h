

// include/User_Setup.h
#ifndef USER_SETUP_LOADED
#define USER_SETUP_LOADED

// === Sterownik Wyświetlacza ===
#define ST7701_DRIVER // Sterownik dla JC8048W55

// === Rozdzielczość ===
#define TFT_WIDTH  480
#define TFT_HEIGHT 800

// === Interfejs SPI ===
// !!! MUSISZ ZNALEŹĆ I WPISAĆ POPRAWNE PINY DLA TWOJEGO MODUŁU !!!
// !!! Poniższe wartości są TYLKO PRZYKŁADAMI !!!
// Sprawdź schemat/dokumentację producenta Twojego modułu ESP32-S3 + Wyświetlacz!
#define TFT_MISO -1  // Zazwyczaj nieużywany przez wyświetlacz w trybie zapisu
#define TFT_MOSI 11  // Przykład - ZMIEŃ! (Pin danych SPI MOSI)
#define TFT_SCLK 12  // Przykład - ZMIEŃ! (Pin zegara SPI SCK)
#define TFT_CS   10  // Przykład - ZMIEŃ! (Pin Chip Select dla wyświetlacza)
#define TFT_DC   13  // Przykład - ZMIEŃ! (Pin Data/Command)
#define TFT_RST  14  // Przykład - ZMIEŃ! (Pin Reset dla wyświetlacza)

// === Pin Podświetlenia (Opcjonalny, ale bardzo ważny) ===
#define TFT_BL   9  // Przykład - ZMIEŃ! (Pin kontroli podświetlenia)
#define TFT_BACKLIGHT_ON HIGH // Sprawdź, czy podświetlenie włącza stan WYSOKI czy NISKI

// === Piny Dotyku GT911 (I2C) ===
// !!! MUSISZ ZNALEŹĆ I WPISAĆ POPRAWNE PINY I2C DLA GT911 !!!
#define TOUCH_SDA 38 // Przykład - ZMIEŃ! (Pin I2C SDA)
#define TOUCH_SCL 39 // Przykład - ZMIEŃ! (Pin I2C SCL)
// Opcjonalne piny dla GT911:
// #define TOUCH_INT 40 // Przykład - ZMIEŃ! (Pin przerwania dotyku)
// #define TOUCH_RST 41 // Przykład - ZMIEŃ! (Pin resetu dotyku)

// === Konfiguracja SPI ===
#define SPI_FREQUENCY        80000000 // ST7701S powinien obsłużyć 80 MHz na ESP32-S3
#define SPI_READ_FREQUENCY   20000000
#define SPI_TOUCH_FREQUENCY  2500000 // Jeśli dotyk używa SPI (GT911 używa I2C)

// === Czcionki ===
#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define LOAD_FONT6
#define LOAD_FONT7
#define LOAD_FONT8
#define LOAD_GFXFF
#define SMOOTH_FONT

#endif // USER_SETUP_LOADED