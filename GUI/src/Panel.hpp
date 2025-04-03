#pragma once

#include <Arduino.h>

class Drawable
{
public:
    Drawable *next; // Pointer to the next drawable object in the list
    Drawable() {} // Constructor
    virtual void draw() = 0; // Pure virtual function for drawing
    virtual ~Drawable() {}   // Virtual destructor for proper cleanup
};

class Button : public Drawable
{
private:
    int _x, _y;          // Position of the button
    int _width, _height; // Size of the button
    String _label;       // Label of the button

public:
    void draw() override
    {
        // Code to draw a button
    }
};

class Panel
{
private:
    int _width;               // Width of the desktop
    int _height;              // Height of the desktop
    uint16_t *_wallpaper; // Pointer to the wallpaper
    uint16_t _backgroundColor;     // Background color of the desktop
    uint16_t _foregroundColor;     // Foreground color of the desktop
    Drawable *_drawables;     // Array of drawable objects
    Drawable *_lastDrawable;  // Pointer to the last drawable object
    int _drawableCount;       // Number of drawables in the array
    int _currentDrawable;     // Index of the currently active drawable

    // uint16_t _sizeOfVideoBuffer; // Size of the video buffer

public:
    Panel(int width, int height) : _width(width), _height(height), _drawableCount(0), _currentDrawable(0)
    {

    }
    ~Panel()
    {

    }
    uint8_t hasWallpaper(); // Check if the panel has a wallpaper
    void setWallpaper(uint16_t *wallpaper); // Set the wallpaper bitmap
    uint16_t *getWallpaper(); // Pointer to the wallpaper bitmap
    void set_backgroundColor(int color);
    void set_foregroundColor(int color);
    void addDrawable(Drawable *drawable);
    void removeDrawable(Drawable *drawable);
    void draw(); // Draw all drawables on the panel
};

class HomePanel : public Panel
{
public:
    HomePanel(int width, int height);
    ~HomePanel();
}