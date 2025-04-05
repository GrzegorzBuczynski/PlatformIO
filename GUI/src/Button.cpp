#pragma once
#include <Arduino.h>
#include "Colors.hpp"
#include "Button.hpp"

Button::Button() : _x(lastX), _y(lastY), _width(50), _height(25), _label(new String("Button")), _colorOn(GREY), _colorOff(DARKGREY), _textColor(WHITE), _pressed(false), prevPressed(false), _action(Button::ActionType::Idle)
{
    lastX += 25;
    lastY += 10;
}

Button::Button(uint16_t x, uint16_t y, uint16_t w, uint16_t h, String *label, uint16_t colorOn, uint16_t colorOff, uint16_t textColor, uint16_t fontSize)
: _x(x), _y(y), _width(w), _height(h), _label(label), _colorOn(colorOn), _colorOff(colorOff), _textColor(textColor), _fontSize(fontSize), _pressed(false), prevPressed(false), _action(Button::ActionType::Idle) {}

Button::~Button() {
    // Destructor implementation (if needed)
    delete _label; // Clean up the dynamically allocated string
    _label = nullptr; // Avoid dangling pointer
}