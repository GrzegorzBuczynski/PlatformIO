// Encapsulated LVGL driver implementation in a C++ class
#ifndef LVGL_DRIVER_H
#define LVGL_DRIVER_H

#include <lvgl.h>

// Always define calibration struct (even if board has no touch) to avoid #ifdef noise in class
typedef struct {
    bool valid;
    float alphaX;
    float betaX;
    float deltaX;
    float alphaY;
    float betaY;
    float deltaY;
} lvgl_touch_calibration_data_t;

#ifdef BOARD_HAS_TOUCH
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
    // Touch calibration data access (for boards with touch)
    const lvgl_touch_calibration_data_t &touchCalibration() const { return touch_calibration_data_; }
    // Set touch calibration data (for boards with touch)
    void setTouchCalibration(const lvgl_touch_calibration_data_t &data) { touch_calibration_data_ = data; }
    lvgl_touch_calibration_data_t touch_calibration_data_ {};
    friend lvgl_touch_calibration_data_t lvgl_compute_touch_calibration(const lv_point_t screen[3], const lv_point_t touch[3]);
        // Periodic helpers (safe to call even jeśli sprzęt niewspierany)
    void animateRgbLed(uint32_t now_ms);
    // Returns mV from CDS or -1 jeśli brak czujnika
    int updateCDSLabel(lv_obj_t * ui_lblCdrValue);
    // Initialize LVGL
    void init();
    
private:
    // Touch calibration data
    // LVGL display and input device handles
    lv_display_t *display_ = nullptr;
    // LVGL input device handle
    lv_indev_t *indev_ = nullptr;
    // return touch calibration data
};

// (Optional) backward compatible free function for simple use cases
// Returns global singleton instance (created on first use)
LvglDriver &lvgl_driver();

#endif // LVGL_DRIVER_H
