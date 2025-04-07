#pragma once
#include <Arduino.h>
#include "GBUButton.hpp"
#include "ScreenParams.hpp"

GBUButton *createButtonGrid(const char **labels, uint16_t *colors);