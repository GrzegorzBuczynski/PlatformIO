# Moduł Screen Rotation - Dokumentacja

Ten moduł zapewnia prostą i elastyczną funkcjonalność obracania ekranu oraz tworzenia przycisków LVGL do sterowania orientacją wyświetlacza w projektach ESP32 Smart Display.

## Pliki modułu

- `screen_rotation.hpp` - Plik nagłówkowy z deklaracjami funkcji
- `screen_rotation.cpp` - Implementacja funkcjonalności obracania
- `example_rotation_usage.cpp` - Przykład użycia bez SquareLine Studio UI

## Funkcje

### `rotate_screen_to_next_orientation(lv_event_t *e = nullptr)`
Obraca ekran do następnej orientacji w sekwencji: 0° → 90° → 180° → 270° → 0°

**Parametry:**
- `e` - Wskaźnik na zdarzenie LVGL (może być NULL)

**Przykład użycia:**
```cpp
// Bezpośrednie obracanie
rotate_screen_to_next_orientation();

// Użycie jako callback dla zdarzenia
void my_button_callback(lv_event_t *e) {
    rotate_screen_to_next_orientation(e);
}
```

### `set_screen_rotation(lv_display_rotation_t rotation)`
Ustawia konkretną orientację ekranu.

**Parametry:**
- `rotation` - Orientacja ekranu:
  - `LV_DISPLAY_ROTATION_0` - 0°
  - `LV_DISPLAY_ROTATION_90` - 90°
  - `LV_DISPLAY_ROTATION_180` - 180°
  - `LV_DISPLAY_ROTATION_270` - 270°

**Przykład użycia:**
```cpp
set_screen_rotation(LV_DISPLAY_ROTATION_90);  // Ustaw orientację poziomą
```

### `get_screen_rotation()`
Pobiera aktualną orientację ekranu.

**Zwraca:** `lv_display_rotation_t` - Aktualna orientacja

**Przykład użycia:**
```cpp
lv_display_rotation_t current = get_screen_rotation();
Serial.printf("Aktualna orientacja: %d\n", current);
```

### `create_rotation_button(...)`
Tworzy przycisk LVGL z automatycznie podłączonym handlerem obracania.

**Parametry:**
- `parent` - Rodzic dla przycisku (obowiązkowy)
- `width` - Szerokość przycisku (domyślnie 100)
- `height` - Wysokość przycisku (domyślnie 50)
- `align` - Wyrównanie (domyślnie `LV_ALIGN_BOTTOM_LEFT`)
- `label_text` - Tekst na przycisku (domyślnie "Rotate")

**Zwraca:** `lv_obj_t*` - Wskaźnik na utworzony przycisk lub NULL w przypadku błędu

**Przykład użycia:**
```cpp
lv_obj_t* screen = lv_scr_act();
lv_obj_t* btn = create_rotation_button(
    screen,                    // parent
    120,                      // width
    60,                       // height
    LV_ALIGN_BOTTOM_CENTER,   // align
    "Obróć"                   // label
);
```

### `rotation_button_event_handler(lv_event_t * e)`
Funkcja callback do użycia z `lv_obj_add_event_cb` dla własnych przycisków.

**Przykład użycia:**
```cpp
lv_obj_t* my_button = lv_button_create(parent);
lv_obj_add_event_cb(my_button, rotation_button_event_handler, LV_EVENT_CLICKED, nullptr);
```

## Przykłady użycia

### 1. Integracja z istniejącym projektem SquareLine Studio

```cpp
#include "screen_rotation.hpp"

void OnRotateClicked(lv_event_t *e)
{
    rotate_screen_to_next_orientation(e);
}
```

### 2. Tworzenie przycisku programowo

```cpp
#include "screen_rotation.hpp"

void setup() {
    smartdisplay_init();
    
    lv_obj_t* screen = lv_scr_act();
    lv_obj_t* rotate_btn = create_rotation_button(
        screen, 
        100, 50, 
        LV_ALIGN_BOTTOM_LEFT, 
        "Rotate"
    );
}
```

### 3. Ręczne ustawianie orientacji

```cpp
#include "screen_rotation.hpp"

void setup() {
    smartdisplay_init();
    
    // Ustaw orientację poziomą na starcie
    set_screen_rotation(LV_DISPLAY_ROTATION_90);
}

void some_function() {
    // Sprawdź aktualną orientację
    if (get_screen_rotation() == LV_DISPLAY_ROTATION_0) {
        Serial.println("Ekran w orientacji pionowej");
    }
}
```

### 4. Pełny przykład bez SquareLine Studio

Zobacz plik `example_rotation_usage.cpp` dla kompletnego przykładu tworzenia interfejsu z funkcją obracania bez użycia SquareLine Studio.

## Integracja

1. Dodaj pliki `screen_rotation.h` i `screen_rotation.cpp` do swojego projektu
2. Załącz nagłówek: `#include "screen_rotation.hpp"`
3. Użyj funkcji zgodnie z powyższymi przykładami

## Wymagania

- ESP32 Smart Display library
- LVGL (włączone w ESP32 Smart Display)
- Arduino framework dla ESP32

## Uwagi

- Wszystkie funkcje zawierają sprawdzanie błędów i logowanie
- Moduł automatycznie obsługuje różne orientacje ekranu
- Funkcje są bezpieczne - sprawdzają poprawność parametrów
- Kompatybilne z wszystkimi wspieranymi wyświetlaczami ESP32 Smart Display
