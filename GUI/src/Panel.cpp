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
    task[0].setColor(BLACK);
    task[1].setText(new TextSprite(new String("Hello World"), 50, 50, WHITE, BLACK, 2));
    task[2].setButton(new Button(60, 200, 100, 40, new String("ON"), RED, GREEN, DARKGREEN, WHITE, 2));
    task[3].setButton(new Button(180, 200, 100, 40, new String("OFF"), RED, RED, DARKGREEN, WHITE, 2));

}

HomePanel::~HomePanel() {
    // Destructor implementation
}
