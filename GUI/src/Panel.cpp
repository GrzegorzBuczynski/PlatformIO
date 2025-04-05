#include "Panel.hpp"
#include "Colors.hpp"
#include "DataTypes.hpp"


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
}

HomePanel::~HomePanel() {
    // Destructor implementation
}
