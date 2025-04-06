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
    Serial.println("Creating HomePanel");
    Serial.print("marilyn_64x64 address: 0x");
    Serial.println((unsigned int)marilyn_64x64, HEX);
    
    // ImageData* imgData = new ImageData(5, 200, 64, 64, marilyn_64x64);
    // Serial.print("Created ImageData object at: 0x");
    // Serial.println((unsigned int)imgData, HEX);
    // Serial.print("With data pointer: 0x");
    // Serial.println((unsigned int)imgData->data, HEX);
    
    task[0].setColor(BLACK);
    task[2].setButton(new Button(60, 200, 100, 40, new String("ON"), RED, GREEN, DARKGREEN, WHITE, 2));
    task[3].setButton(new Button(180, 200, 100, 40, new String("OFF"), RED, RED, DARKGREEN, WHITE, 2));
    task[1].setImage(new ImageData(5, 200, 64, 64, marilyn_64x64));
    task[1].setImage(new ImageData(5, 300, 64, 64, marilyn_64x64));
    task[4].setText(new TextSprite(new String("Hello World"), 50, 50, WHITE, BLACK, 2));
}

HomePanel::~HomePanel() {
    // Destructor implementation
}
