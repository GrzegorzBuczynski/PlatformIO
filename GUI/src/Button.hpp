#pragma once

#include <Arduino.h>
#include "Colors.hpp"

class Button
{
private:
public:
    enum class ActionType
    {
        ChangePanel,
        Confirm,
        Pressed,
        Released,
        Idle
    };
    uint16_t _x, _y;              // Coordinates of the top-left corner
    static uint16_t lastX, lastY; // Coordinates of the top-left corner
    int _width, _height;          // Size of the button
    String *_label;                // Label of the button
    uint16_t _colorOn;            // Color of the button
    uint16_t _colorOff;           // Color of the button when not pressed
    uint16_t _textColor;          // Text color of the button
    uint16_t _fontSize;           // Font size of the button text
    bool _pressed;                // State of the button (pressed or not)
    bool prevPressed;             // Previous state of the button
    Button::ActionType _action;           // Action associated with the button
    int _actionParam;             // Parameter for the action associated with the button

    Button();
    Button(uint16_t x, uint16_t y, uint16_t w, uint16_t h, String *label, uint16_t colorOn, uint16_t colorOff, uint16_t textColor, uint16_t fontSize);
    ~Button();
};