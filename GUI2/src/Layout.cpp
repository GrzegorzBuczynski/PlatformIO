#include "Layout.hpp"


// Struktura pomocnicza do przechowywania parametrów układu siatki
typedef struct {
    int numCols;
    int numRows;
    int buttonWidth;
    int buttonHeight;
    int screenPaddingX;
    int screenPaddingY;
    int buttonSpacing;
} GridLayout;

// Funkcja obliczająca wymiary ekranu w zależności od trybu widoku
void getScreenDimensions(int *screenWidth, int *screenHeight) {
#if VIEW_MODE == LANDSCAPE
    *screenWidth = SCREEN_WIDTH_LANDSCAPE;
    *screenHeight = SCREEN_HEIGHT_LANDSCAPE;
#else
    *screenWidth = SCREEN_WIDTH_PORTRAIT;
    *screenHeight = SCREEN_HEIGHT_PORTRAIT;
#endif
}

// Funkcja obliczająca liczbę etykiet (długość tablicy zakończonej nullptr)
int countLabels(const char **labels) {
    int labelCount = 0;
    while (labels[labelCount] != nullptr) {
        labelCount++;
    }
    return labelCount;
}

// Funkcja obliczająca optymalny układ siatki przycisków
GridLayout calculateGridLayout(int labelCount, int screenWidth, int screenHeight) {
    GridLayout layout;
    
    // Ustalamy podstawowe paddingi
    layout.screenPaddingX = screenWidth * 0.05;                   // 5% szerokości ekranu
    layout.screenPaddingY = screenHeight * 0.05;                  // 5% wysokości ekranu
    layout.buttonSpacing = min(screenWidth, screenHeight) * 0.02; // 2% mniejszego wymiaru ekranu

    // Obliczamy optymalną liczbę kolumn i wierszy na podstawie proporcji ekranu
    layout.numCols = sqrt(labelCount * screenWidth / screenHeight);
    if (layout.numCols < 1)
        layout.numCols = 1;

    layout.numRows = (labelCount + layout.numCols - 1) / layout.numCols; // Zaokrąglenie w górę

    // Dostosowanie liczby kolumn, jeśli ostatni wiersz byłby zbyt pusty
    if (layout.numRows > 1) {
        int buttonsInLastRow = labelCount - (layout.numRows - 1) * layout.numCols;
        if (buttonsInLastRow < layout.numCols / 2) {
            layout.numCols = (labelCount + layout.numRows - 1) / layout.numRows;
            layout.numRows = (labelCount + layout.numCols - 1) / layout.numCols;
        }
    }

    // Dostępny obszar na ekranie po odjęciu paddingów
    int availableWidth = screenWidth - (2 * layout.screenPaddingX);
    int availableHeight = screenHeight - (2 * layout.screenPaddingY);

    // Obliczenie wymiarów pojedynczego przycisku
    layout.buttonWidth = (availableWidth - (layout.buttonSpacing * (layout.numCols - 1))) / layout.numCols;
    layout.buttonHeight = (availableHeight - (layout.buttonSpacing * (layout.numRows - 1))) / layout.numRows;

    return layout;
}

// Funkcja pobierająca kolor dla przycisku, z obsługą przypadków błędów
uint16_t getButtonColor(Color1 *colors, int index) {
    if (colors == nullptr) {
        return BLUE; // Domyślny kolor, gdy colors to nullptr
    }
    Color1 *current = colors;
    for (int i = 0; i < index && current != nullptr; i++) {
        current = current->next;
    }
    if (current != nullptr) {
        return current->color; // Zwróć kolor przycisku
    } else {
        return BLUE; // Domyślny kolor, gdy index jest poza zakresem
    }
}

// Funkcja tworząca pojedynczy przycisk
GBUButton* createButton(int x, int y, int width, int height, const char* label, uint16_t color) {
    GBUButton* button = new GBUButton;
    button->x = x;
    button->y = y;
    button->w = width;
    button->h = height;
    button->label = label;
    button->color = color;
    button->next = nullptr;
    return button;
}

// Główna funkcja tworząca siatkę przycisków
GBUButton* createButtonGrid(uint16_t amount, const char **labels, uint16_t *colors) {
    // Określenie dostępnych wymiarów ekranu
    int screenWidth, screenHeight;
    getScreenDimensions(&screenWidth, &screenHeight);

    // Obliczenie liczby etykiet
    Serial.print("Label count: ");
    Serial.println(amount); // Debugging: wypisz liczbę etykiet

    if (amount == 0) {
        return nullptr; // Brak przycisków do utworzenia
    }

    // Obliczenie parametrów układu siatki
    GridLayout layout = calculateGridLayout(amount, screenWidth, screenHeight);

    // Utworzenie pierwszego przycisku (głowa listy)
    GBUButton *head = nullptr;
    GBUButton *current = nullptr;

    uint16_t buttonIndex = 0;

    for (int row = 0; row < layout.numRows && buttonIndex < amount; row++) {
        for (int col = 0; col < layout.numCols && buttonIndex < amount; col++) {
            // Obliczenie pozycji przycisku
            int x = layout.screenPaddingX + col * (layout.buttonWidth + layout.buttonSpacing);
            int y = layout.screenPaddingY + row * (layout.buttonHeight + layout.buttonSpacing);

            // Pobranie koloru przycisku
            // uint16_t color = getButtonColor(colors, buttonIndex);
            Serial.print(" Button color: ");
            Serial.println(colors[buttonIndex], HEX); // Debugging: wypisz kolor przycisku

            // Utworzenie nowego przycisku
            GBUButton *newButton = createButton(x, y, layout.buttonWidth, layout.buttonHeight, 
                                              labels[buttonIndex], colors[buttonIndex]);

            // Dodanie do listy
            if (head == nullptr) {
                head = newButton;
                current = newButton;
            } else {
                current->next = newButton;
                current = newButton;
            }

            buttonIndex++;
        }
    }

    return head;
}