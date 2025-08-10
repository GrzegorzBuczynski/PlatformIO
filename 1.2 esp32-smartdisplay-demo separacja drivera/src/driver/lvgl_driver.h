#ifndef LVGL_DRIVER_H
#define LVGL_DRIVER_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

void lvgl_driver_init();
// Prosta kontrola binarnego podświetlenia (dla paneli bez PWM)
void lvgl_backlight_set(bool on);
// Backlight, adaptive brightness and RGB LED APIs are provided by the core library (esp32_smartdisplay_optimized).

#ifdef BOARD_HAS_TOUCH
typedef struct {
    bool valid;
    float alphaX;
    float betaX;
    float deltaX;
    float alphaY;
    float betaY;
    float deltaY;
} lvgl_touch_calibration_data_t;

extern lvgl_touch_calibration_data_t lvgl_touch_calibration_data;
lvgl_touch_calibration_data_t lvgl_compute_touch_calibration(const lv_point_t screen[3], const lv_point_t touch[3]);
#endif

#ifdef __cplusplus
}
#endif

#endif // LVGL_DRIVER_H
