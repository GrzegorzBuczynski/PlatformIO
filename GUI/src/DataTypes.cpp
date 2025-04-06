#include "DataTypes.hpp"
#include "Colors.hpp"

TextSprite::TextSprite() : text(new String("Hello World")), x(0), y(0), color(WHITE), bgColor(BLACK), fontSize(2) {
    // Constructor implementation
}

ImageData::ImageData(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint16_t *data) 
: x(x), y(y), width(width), height(height), data(data) {}

TextSprite::TextSprite(String *text, uint16_t x, uint16_t y,  uint16_t color, uint16_t bgColor, uint16_t fontSize) : text(text), x(x), y(y), color(color), bgColor(bgColor), fontSize(fontSize) {
    // Constructor implementation
}
TextSprite::~TextSprite() {
    // Destructor implementation
    if (text) {
        delete text; // Clean up the dynamically allocated string
        text = nullptr; // Avoid dangling pointer
    }
}