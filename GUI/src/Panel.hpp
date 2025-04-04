#pragma once

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>

class Drawable
{
public:
    Drawable *next; // Pointer to the next drawable object in the list
    Drawable() {} // Constructor
    virtual void draw() = 0; // Pure virtual function for drawing
    virtual ~Drawable() {}   // Virtual destructor for proper cleanup
};


class Panel
{
private:
    int _rotation;           // Rotation of the panel
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

    Panel(int width, int height);
    Panel(); // Default constructor
    ~Panel();
    
    void setWidth(int width); // Set the width of the panel
    void setHeight(int height); // Set the height of the panel
    void setWallpaper(uint16_t *wallpaper); // Set the wallpaper bitmap
    void setBackgroundColor(int color);
    void setForegroundColor(int color);
    void setDesktopColor(int color); // Set the desktop color
    void setRotation(int rotation); // Set the rotation of the panel
    
    int get_width() const { return _width; } // Get the width of the panel
    int get_height() const { return _height; } // Get the height of the panel
    int get_rotation() const; // Get the rotation of the panel
    int get_backgroundColor() const { return _backgroundColor; } // Get the background color
    int get_foregroundColor() const { return _foregroundColor; } // Get the foreground color
    uint16_t *getWallpaper(); // Pointer to the wallpaper bitmap
    
    uint8_t hasWallpaper(); // Check if the panel has a wallpaper

    void draw(); // Draw all drawables on the panel
    void removeDrawable(Drawable *drawable);
    void addDrawable(Drawable *drawable);
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

class HomePanel : public Panel
{
private:

public:
    HomePanel(); // Default constructor
    HomePanel(int width, int height);
    void draw(); 
 
};
