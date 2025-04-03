#include "Panel.hpp"

void Panel::set_backgroundColor(int color)
{
    _backgroundColor = color;
    if (_backgroundColor == _foregroundColor)
    {
        _foregroundColor = 0xFFFFFF - _backgroundColor; // Invert color for contrast
    }
}
void Panel::set_foregroundColor(int color)
{
    _foregroundColor = color;
    if (_backgroundColor == _foregroundColor)
    {
        _backgroundColor = 0xFFFFFF - _foregroundColor; // Invert color for contrast
    }
}

HomePanel::HomePanel(int width, int height) : Panel(width, height)
{
    // Initialize the home panel with specific properties
    set_backgroundColor(0x000000); // Black background
    set_foregroundColor(0xFFFFFF); // White foreground
}
HomePanel::~HomePanel()
{
    // Cleanup if needed
}
void Panel::addDrawable(Drawable *drawable)
{
    if (_drawableCount < 10) // Assuming a maximum of 10 drawables
    {
        drawable->next = _drawables;
        _drawables = drawable;
    }
    else
    {
        Serial.println("Max drawable limit reached!");
    }
}