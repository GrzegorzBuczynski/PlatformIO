#include "Panel.hpp"
#include "Colors.hpp"
#include "DataTypes.hpp"
#include "Button.hpp"


Panel::Panel() {
    // Constructor implementation
}

Panel::~Panel() {
    // Destructor implementation
}


HomePanel::HomePanel() {
    // Constructor implementation
    task[0].setColor(RED);
    task[1].setText(new TextSprite(new String("Hello World"), 50, 50, WHITE, BLACK, 2));
    task[2].setButton(new Button(100, 100, 80, 40, new String("Click Me"), GREEN, DARKGREEN, WHITE, 2));
    // Button(uint16_t x, uint16_t y, uint16_t w, uint16_t h, String *label, uint16_t colorOn, uint16_t colorOff, uint16_t textColor);

}

HomePanel::~HomePanel() {
    // Destructor implementation
}
