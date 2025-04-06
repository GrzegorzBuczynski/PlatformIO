#pragma once
#include <Arduino.h>
#include "DataTypes.hpp"
#include "Button.hpp"
// #include "Panel.hpp"

#define MAX_ACTIONS 10 // Maksymalna liczba akcji

// Deklaracje typów pomocniczych
enum class TaskType {
    None,
    Text,
    Color,
    Imagee,
    Panel,
    Button
};

// struct String;     // Forward declarations
// struct ImageData;
struct Panel;
// struct Button;

union TaskValue {
    TextSprite* text;
    uint16_t color;
    ImageData* image;
    Panel* panel;
    Button* button;
    Button* buttonData;

    TaskValue() : text(nullptr) {}
};

class Task {
public:	
    TaskType type;
    TaskValue value;

    Task();
    ~Task();

    void setText(TextSprite* ptr);
    void setColor(uint16_t c);
    void setImage(ImageData* img);
    void setImage();
    void setPanel(Panel* p);
    void setButton(Button* b);
    void clear();
};
