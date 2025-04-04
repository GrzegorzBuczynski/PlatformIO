#pragma once

#include <Arduino.h>
#include <Panel.hpp>
#include <MyDisplay.hpp>
// #include <lilOS.h>

// enum apps
// {
//         homeApp = HOME_PANEL_ID,
//         calcApp,
//         breakoutApp,
//         /*testApp*/ iconEditApp /*, starTrekApp*/
// };


class MyOS
{
private:
        MyDisplay display; // The device we are running on.
        Panel *panel; // The home panel.

public:
        MyOS(void);
        ~MyOS(void);

        // virtual int begin(void);                // The hardware is online, do hookups.
        // virtual Panel createPanel(int panelID); // We need to write our own panel creation method.
        //                                         // void     backlightOn(void);
        // virtual void beep(void);                // Only WE know how to make it beep.
        // virtual int getTonePin(void);
        // virtual void setBrightness(byte brightness); // 0 for full bright 255 for off.
        // virtual char *getSystemFolder(void);
        // virtual char *getPanelFolder(int panelID);
};

// extern bmpMask iconMask;
