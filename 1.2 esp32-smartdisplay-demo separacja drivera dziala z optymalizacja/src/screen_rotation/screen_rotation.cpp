#include "screen_rotation.hpp"
#include <Arduino.h>

void rotate_screen_to_next_orientation(lv_event_t *e)
{
    // Pobierz domyślny ekran
    auto disp = lv_display_get_default();
    if (disp == nullptr) {
        Serial.println("Error: Cannot get default display");
        return;
    }
    
    // Pobierz aktualną rotację i przejdź do następnej
    auto current_rotation = lv_display_get_rotation(disp);
    auto next_rotation = (lv_display_rotation_t)((current_rotation + 1) % (LV_DISPLAY_ROTATION_270 + 1));
    
    // Ustaw nową rotację
    lv_display_set_rotation(disp, next_rotation);
    
    // Wyświetl informację o zmianie orientacji
    const char* rotation_names[] = {"0°", "90°", "180°", "270°"};
    Serial.printf("Screen rotated to: %s\n", rotation_names[next_rotation]);
}

void set_screen_rotation(lv_display_rotation_t rotation)
{
    auto disp = lv_display_get_default();
    if (disp == nullptr) {
        Serial.println("Error: Cannot get default display");
        return;
    }
    
    // Sprawdź czy rotacja jest prawidłowa
    if (rotation < LV_DISPLAY_ROTATION_0 || rotation > LV_DISPLAY_ROTATION_270) {
        Serial.printf("Error: Invalid rotation value: %d\n", rotation);
        return;
    }
    
    lv_display_set_rotation(disp, rotation);
    
    const char* rotation_names[] = {"0°", "90°", "180°", "270°"};
    Serial.printf("Screen rotation set to: %s\n", rotation_names[rotation]);
}

lv_display_rotation_t get_screen_rotation()
{
    auto disp = lv_display_get_default();
    if (disp == nullptr) {
        Serial.println("Error: Cannot get default display");
        return LV_DISPLAY_ROTATION_0;
    }
    
    return lv_display_get_rotation(disp);
}

lv_obj_t* create_rotation_button(lv_obj_t* parent, 
                                 lv_coord_t width, 
                                 lv_coord_t height,
                                 lv_align_t align,
                                 const char* label_text)
{
    if (parent == nullptr) {
        Serial.println("Error: Parent object is null");
        return nullptr;
    }
    
    // Utwórz przycisk
    lv_obj_t* button = lv_button_create(parent);
    if (button == nullptr) {
        Serial.println("Error: Failed to create rotation button");
        return nullptr;
    }
    
    // Ustaw rozmiar i pozycję
    lv_obj_set_width(button, width);
    lv_obj_set_height(button, height);
    lv_obj_set_align(button, align);
    
    // Ustaw flagi
    lv_obj_add_flag(button, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_remove_flag(button, LV_OBJ_FLAG_SCROLLABLE);
    
    // Utwórz etykietę na przycisku
    lv_obj_t* label = lv_label_create(button);
    if (label != nullptr) {
        lv_obj_set_width(label, LV_SIZE_CONTENT);
        lv_obj_set_height(label, LV_SIZE_CONTENT);
        lv_obj_set_align(label, LV_ALIGN_CENTER);
        lv_label_set_text(label, label_text);
    }
    
    // Dodaj event handler
    lv_obj_add_event_cb(button, rotation_button_event_handler, LV_EVENT_CLICKED, nullptr);
    
    Serial.printf("Rotation button created with label: '%s'\n", label_text);
    
    return button;
}

void rotation_button_event_handler(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    
    if (event_code == LV_EVENT_CLICKED) {
        rotate_screen_to_next_orientation(e);
    }
}
