// Encapsulated LVGL driver implementation in a C++ class
#ifndef LVGL_DRIVER_H
#define LVGL_DRIVER_H

#include <lvgl.h>

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

lvgl_touch_calibration_data_t lvgl_compute_touch_calibration(const lv_point_t screen[3], const lv_point_t touch[3]);
#endif

class LvglDriver {
public:
    LvglDriver(); // Performs init during construction
    ~LvglDriver() = default;

    // Rotation helper
    void setRotation(lv_display_rotation_t rotation);
    // Simple binary backlight control (for panels without PWM)
    void setBacklight(bool on);

    lv_display_t *display() const { return display_; }

#ifdef BOARD_HAS_TOUCH
    const lvgl_touch_calibration_data_t &touchCalibration() const { return touch_calibration_data_; }
    void setTouchCalibration(const lvgl_touch_calibration_data_t &data) { touch_calibration_data_ = data; }
#endif

private:
    void init();
    lv_display_t *display_ = nullptr;
#ifdef BOARD_HAS_TOUCH
    lv_indev_t *indev_ = nullptr;
public: // (temporarily public for internal C callback access)
    lvgl_touch_calibration_data_t touch_calibration_data_ {};
private:
    friend lvgl_touch_calibration_data_t lvgl_compute_touch_calibration(const lv_point_t screen[3], const lv_point_t touch[3]);
#endif
};

// (Optional) backward compatible free function for simple use cases
// Returns global singleton instance (created on first use)
LvglDriver &lvgl_driver();

#endif // LVGL_DRIVER_H
