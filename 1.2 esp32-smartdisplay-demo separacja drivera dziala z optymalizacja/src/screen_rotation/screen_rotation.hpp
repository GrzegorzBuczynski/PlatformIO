#pragma once

#include <esp32_smartdisplay.h>

/**
 * @brief Funkcja obracająca ekran do następnej orientacji
 * Przełącza między: 0° -> 90° -> 180° -> 270° -> 0°
 * 
 * @param e Wskaźnik na zdarzenie LVGL (może być NULL)
 */
void rotate_screen_to_next_orientation(lv_event_t *e = nullptr);

/**
 * @brief Ustawia konkretną orientację ekranu
 * 
 * @param rotation Rotacja ekranu (LV_DISPLAY_ROTATION_0, LV_DISPLAY_ROTATION_90, 
 *                 LV_DISPLAY_ROTATION_180, LV_DISPLAY_ROTATION_270)
 */
void set_screen_rotation(lv_display_rotation_t rotation);

/**
 * @brief Pobiera aktualną orientację ekranu
 * 
 * @return lv_display_rotation_t Aktualna rotacja ekranu
 */
lv_display_rotation_t get_screen_rotation();

/**
 * @brief Tworzy przycisk LVGL do obracania ekranu
 * 
 * @param parent Rodzic dla przycisku (np. ekran lub panel)
 * @param width Szerokość przycisku w pikselach
 * @param height Wysokość przycisku w pikselach
 * @param align Wyrównanie przycisku (np. LV_ALIGN_BOTTOM_LEFT)
 * @param label_text Tekst wyświetlany na przycisku (domyślnie "Rotate")
 * @return lv_obj_t* Wskaźnik na utworzony przycisk
 */
lv_obj_t* create_rotation_button(lv_obj_t* parent, 
                                 lv_coord_t width = 100, 
                                 lv_coord_t height = 50,
                                 lv_align_t align = LV_ALIGN_BOTTOM_LEFT,
                                 const char* label_text = "Rotate");

/**
 * @brief Funkcja callback dla przycisku obracania - do użycia z lv_obj_add_event_cb
 */
void rotation_button_event_handler(lv_event_t * e);
