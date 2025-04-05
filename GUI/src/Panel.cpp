#include "Panel.hpp"
#include "Colors.hpp"


Panel::Panel() {
    // Constructor implementation
}

Panel::~Panel() {
    // Destructor implementation
}



// ~HomePanel() {
//     // Destructor implementation
// }

// Panel::Panel(int width, int height) : _width(width), _height(height), _rotation(0), _backgroundColor(0x000000), _foregroundColor(0xFFFFFF), _drawableCount(0), _currentDrawable(0)
// {
//     _drawables = nullptr; // Initialize the drawable list to null
// }
// Panel::Panel() {}
// Panel::~Panel(){}

// void Panel::setBackgroundColor(int color)
// {
//     _backgroundColor = color;
//     if (_backgroundColor == _foregroundColor)
//     {
//         _foregroundColor = 0xFFFFFF - _backgroundColor; // Invert color for contrast
//     }
// }
// void Panel::setForegroundColor(int color)
// {
//     _foregroundColor = color;
//     if (_backgroundColor == _foregroundColor)
//     {
//         _backgroundColor = 0xFFFFFF - _foregroundColor; // Invert color for contrast
//     }
// }

// void Panel::addDrawable(Drawable *drawable)
// {
//     if (_drawableCount < 10) // Assuming a maximum of 10 drawables
//     {
//         drawable->next = _drawables;
//         _drawables = drawable;
//     }
//     else
//     {
//         Serial.println("Max drawable limit reached!");
//     }
// }

// void Panel::setWallpaper(uint16_t *wallpaper){}
// void Panel::setWidth(int width) { _width = width; }
// void Panel::setHeight(int height) { _height = height; }

// HomePanel::HomePanel(){
//     // setWidth(420); // Set the width of the panel
//     // setHeight(280); // Set the height of the panel
//     // setDesktopColor(0x000000); // Set default desktop color
//     // setBackgroundColor(0x000000); // Set default background color
//     // setForegroundColor(0xFF); // Set default foreground color
//     // setRotation(0); // Set default rotation
//     // addDrawable(new Button()); // Add a button as an example drawable


// }
