/*
 * UWAGA: To jest plik przykładowy demonstrujący użycie modułu screen_rotation.
 * Funkcje setup() i loop() zostały zmienione na example_setup() i example_loop()
 * aby uniknąć konfliktów z głównym plikiem main.cpp podczas kompilacji.
 * 
 * Aby użyć tego przykładu:
 * 1. Skopiuj zawartość funkcji example_setup() do głównej funkcji setup()
 * 2. Skopiuj zawartość funkcji example_loop() do głównej funkcji loop()
 * 3. Lub użyj tego pliku jako referencji do implementacji własnego interfejsu
 */

#include <Arduino.h>
#include <esp32_smartdisplay.h>
#include "screen_rotation.hpp"

// Przykład użycia modułu screen_rotation bez SquareLine Studio UI

lv_obj_t* main_screen;
lv_obj_t* rotation_button;
lv_obj_t* info_label;

void example_setup_simple_ui()
{
    // Utwórz główny ekran
    main_screen = lv_obj_create(nullptr);
    lv_scr_load(main_screen);
    
    // Utwórz etykietę z informacjami
    info_label = lv_label_create(main_screen);
    lv_obj_set_width(info_label, LV_SIZE_CONTENT);
    lv_obj_set_height(info_label, LV_SIZE_CONTENT);
    lv_obj_set_align(info_label, LV_ALIGN_CENTER);
    lv_label_set_text(info_label, "Kliknij przycisk aby obrocic ekran");
    
    // Utwórz przycisk obracania używając wyizolowanego modułu
    rotation_button = create_rotation_button(
        main_screen,        // parent
        120,               // width
        60,                // height
        LV_ALIGN_BOTTOM_LEFT,  // align - użycie dostępnej wartości
        "Obróć"           // label text
    );
    
    // Sprawdź czy przycisk został utworzony poprawnie
    if (rotation_button == nullptr) {
        Serial.println("Błąd: Nie udało się utworzyć przycisku obracania!");
    }
}

void example_update_info_label()
{
    static uint32_t last_update = 0;
    uint32_t now = millis();
    
    if (now - last_update > 1000) {  // Aktualizuj co sekundę
        last_update = now;
        
        // Pobierz aktualną orientację
        lv_display_rotation_t current_rotation = get_screen_rotation();
        const char* rotation_names[] = {"0°", "90°", "180°", "270°"};
        
        // Aktualizuj tekst etykiety
        lv_label_set_text_fmt(info_label, 
            "Aktualna orientacja: %s\nKliknij przycisk aby obrocic ekran\nCzas: %u ms", 
            rotation_names[current_rotation], 
            (unsigned int)now);
    }
}

void example_setup()
{
#ifdef ARDUINO_USB_CDC_ON_BOOT
    delay(5000);
#endif
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    log_i("Board: %s", BOARD_NAME);
    log_i("Przykład użycia modułu screen_rotation");

    // Inicjalizuj smart display
    smartdisplay_init();

    // Skonfiguruj prosty interfejs
    example_setup_simple_ui();
    
    Serial.println("Inicjalizacja zakończona. Naciśnij przycisk aby obrócić ekran.");
}

auto example_lv_last_tick = millis();

void example_loop()
{
    auto const now = millis();
    
    // Aktualizuj informacje na etykiecie
    example_update_info_label();
    
    // Aktualizuj LVGL
    lv_tick_inc(now - example_lv_last_tick);
    example_lv_last_tick = now;
    lv_timer_handler();
}
