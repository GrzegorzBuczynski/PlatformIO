#pragma once

#include <Arduino.h>
#include <Panel.hpp>
// #include <lilOS.h>

// enum apps
// {
//         homeApp = HOME_PANEL_ID,
//         calcApp,
//         breakoutApp,
//         /*testApp*/ iconEditApp /*, starTrekApp*/
// };

class MyDisplay
{
private:
        int _width;               // Width of the display
        int _height;              // Height of the display
        uint8_t *_videoBuffer;    // Pointer to the video buffer
        uint16_t _sizeOfVideoBuffer; // Size of the video buffer
        Panel _Panel; // Pointer to the home panel
public:
        MyDisplay(int width, int height, uint8_t *videoBuffer);
        ~MyDisplay();
        void set_backgroundColor(int color);
        void set_foregroundColor(int color);
        void draw();
};

class MyOS
{
private:
        MyDisplay *display; // The device we are running on.
        Panel *homePanel; // The home panel.

public:
        MyOS(void);
        virtual ~MyOS(void);

        virtual int begin(void);                // The hardware is online, do hookups.
        virtual Panel createPanel(int panelID); // We need to write our own panel creation method.
                                                // void     backlightOn(void);
        virtual void beep(void);                // Only WE know how to make it beep.
        virtual int getTonePin(void);
        virtual void setBrightness(byte brightness); // 0 for full bright 255 for off.
        virtual char *getSystemFolder(void);
        virtual char *getPanelFolder(int panelID);
};

// extern bmpMask iconMask;
