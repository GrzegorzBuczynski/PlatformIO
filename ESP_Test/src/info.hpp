//https://www.surenoo.com/products/23291185
// liblary TFT_eSPI 
// st7262  ESP Display Panel handles this driver
// P050B028-IPS-CTP display panel
// 800x480 resolution
// if event_code == LV_EVENT_CLICKED lub event_code == released();
// lv_obj_t *target = lv_event_get_target(e); z kordynat z elementów na planszy lub z seriala
// if target != null set flag to update screen
// update object parameters object now how to parse json data update object
// remove event flag
// dodaj funkcje która zaktualizuje która plansza jest aktualnie wyświetlana void update_screen(int screen_id)


//GT911 – sterownik dotyku to GT911, czyli powszechnie stosowany pojemnościowy kontroler dotyku (I2C)
// ​Analiza oprogramowania układowego wyświetlacza:​

// Jeśli masz fizyczny dostęp do wyświetlacza z wgranym oprogramowaniem, możesz spróbować zgrać jego zawartość 
//za pomocą narzędzi takich jak esptool.​

// LVGL 8.3.7 – wyświetlacz używa LVGL (Light and Versatile Graphics Library), bardzo popularnej biblioteki GUI dla mikrokontrolerów.

// GT911 – sterownik dotyku to GT911, czyli powszechnie stosowany pojemnościowy kontroler dotyku (I2C).

// esp_lcd_touch.c – sugeruje, że użyto frameworka ESP-IDF z esp_lcd_touch, czyli oficjalnego API do obsługi dotyku w ESP32.

// Pamiętaj, że odczytanie i analiza skompilowanego kodu binarnego może być skomplikowane i czasochłonne.