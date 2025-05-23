#pragma once

#include <Arduino.h>
#include "Task.hpp"
#include "bitmap_RGB.h"



class Panel
{
    public:
        Panel(); // Default constructor
        ~Panel(); // Destructor
        Task task[MAX_ACTIONS]; // Array of tasks
};


class HomePanel : public Panel
{
public:
    HomePanel(); // Default constructor
    ~HomePanel();
};
