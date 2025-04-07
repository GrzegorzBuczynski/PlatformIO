#include "Layout.hpp"




GBUButton *createButtonGrid(const char **labels, uint16_t *colors)
{
    // Określenie dostępnych wymiarów ekranu
    int screenWidth, screenHeight;

#if VIEW_MODE == LANDSCAPE
    screenWidth = SCREEN_WIDTH_LANDSCAPE;
    screenHeight = SCREEN_HEIGHT_LANDSCAPE;
#else
    screenWidth = SCREEN_WIDTH_PORTRAIT;
    screenHeight = SCREEN_HEIGHT_PORTRAIT;
#endif

    // Obliczenie liczby etykiet
    int labelCount = 0;
    while (labels[labelCount] != nullptr)
    {
        labelCount++;
    }

    if (labelCount == 0)
    {
        return nullptr; // Brak przycisków do utworzenia
    }

    // Ustalamy podstawowe paddingi
    const int screenPaddingX = screenWidth * 0.05;                   // 5% szerokości ekranu
    const int screenPaddingY = screenHeight * 0.05;                  // 5% wysokości ekranu
    const int buttonSpacing = min(screenWidth, screenHeight) * 0.02; // 2% mniejszego wymiaru ekranu

    // Obliczamy optymalną liczbę kolumn i wierszy na podstawie proporcji ekranu
    int numCols = sqrt(labelCount * screenWidth / screenHeight);
    if (numCols < 1)
        numCols = 1;

    int numRows = (labelCount + numCols - 1) / numCols; // Zaokrąglenie w górę

    // Dostosowanie liczby kolumn, jeśli ostatni wiersz byłby zbyt pusty
    if (numRows > 1)
    {
        int buttonsInLastRow = labelCount - (numRows - 1) * numCols;
        if (buttonsInLastRow < numCols / 2)
        {
            numCols = (labelCount + numRows - 1) / numRows;
            numRows = (labelCount + numCols - 1) / numCols;
        }
    }

    // Dostępny obszar na ekranie po odjęciu paddingów
    int availableWidth = screenWidth - (2 * screenPaddingX);
    int availableHeight = screenHeight - (2 * screenPaddingY);

    // Obliczenie wymiarów pojedynczego przycisku
    int buttonWidth = (availableWidth - (buttonSpacing * (numCols - 1))) / numCols;
    int buttonHeight = (availableHeight - (buttonSpacing * (numRows - 1))) / numRows;

    // Utworzenie pierwszego przycisku (głowa listy)
    GBUButton *head = nullptr;
    GBUButton *current = nullptr;

    int buttonIndex = 0;

    for (int row = 0; row < numRows && buttonIndex < labelCount; row++)
    {
        for (int col = 0; col < numCols && buttonIndex < labelCount; col++)
        {
            // Obliczenie pozycji przycisku
            int x = screenPaddingX + col * (buttonWidth + buttonSpacing);
            int y = screenPaddingY + row * (buttonHeight + buttonSpacing);

            // Utworzenie nowego przycisku
            GBUButton *newButton = new GBUButton;
            newButton->x = x;
            newButton->y = y;
            newButton->w = buttonWidth;
            newButton->h = buttonHeight;
            newButton->label = labels[buttonIndex];
            newButton->color = colors[buttonIndex]; // Zakładam, że pierwszy element z tablicy kolorów
            newButton->next = nullptr;

            // Dodanie do listy
            if (head == nullptr)
            {
                head = newButton;
                current = newButton;
            }
            else
            {
                current->next = newButton;
                current = newButton;
            }

            buttonIndex++;
        }
    }

    return head;
}