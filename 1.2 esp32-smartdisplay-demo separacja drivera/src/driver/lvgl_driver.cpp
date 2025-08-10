// Class based driver implementation
#include "lvgl_driver.h"
#include <Arduino.h>
#include <esp_lcd_panel_ops.h>
#include <esp32_smartdisplay.h>

// Prototypes from optimized C sources (not included as .c inside C++)
extern "C" {
  lv_display_t *lvgl_lcd_init();
  lv_indev_t *lvgl_touch_init();
}

// Include hardware configuration
#if defined(JC8048W550)
#include "config/display_JC8048W550.h"
#else
#error "Board not supported!"
#endif

#ifdef BOARD_HAS_TOUCH
static void (*driver_touch_read_cb)(lv_indev_t *indev, lv_indev_data_t *data) = nullptr;
// Keep a pointer to the active driver instance for calibration access inside C callback
static class LvglDriver *s_lvgl_driver_instance = nullptr;
#endif

#ifdef LV_USE_LOG
static void lvgl_log(lv_log_level_t level, const char *buf)
{
  switch (level)
  {
  case LV_LOG_LEVEL_TRACE:
    log_printf("%s", buf);
    break;
  case LV_LOG_LEVEL_INFO:
    log_i("%s", buf);
    break;
  case LV_LOG_LEVEL_WARN:
    log_w("%s", buf);
    break;
  case LV_LOG_LEVEL_ERROR:
    log_e("%s", buf);
    break;
  }
}
#endif

// Remove duplicated brightness / backlight / LED implementations; rely on library versions.

#ifdef BOARD_HAS_TOUCH
static void lvgl_touch_calibration_transform(lv_indev_t *indev, lv_indev_data_t *data)
{
  driver_touch_read_cb(indev, data);
  if (s_lvgl_driver_instance && s_lvgl_driver_instance->touch_calibration_data_.valid && data->state == LV_INDEV_STATE_PRESSED)
  {
    lv_point_t pt = {
        .x = (int32_t)roundf(data->point.x * s_lvgl_driver_instance->touch_calibration_data_.alphaX + data->point.y * s_lvgl_driver_instance->touch_calibration_data_.betaX + s_lvgl_driver_instance->touch_calibration_data_.deltaX),
        .y = (int32_t)roundf(data->point.x * s_lvgl_driver_instance->touch_calibration_data_.alphaY + data->point.y * s_lvgl_driver_instance->touch_calibration_data_.betaY + s_lvgl_driver_instance->touch_calibration_data_.deltaY)};
    data->point = pt;
  }
}

lvgl_touch_calibration_data_t lvgl_compute_touch_calibration(const lv_point_t screen[3], const lv_point_t touch[3])
{
  const float delta = ((touch[0].x - touch[2].x) * (touch[1].y - touch[2].y)) - ((touch[1].x - touch[2].x) * (touch[0].y - touch[2].y));
  return {
      .valid = true,
      .alphaX = (((screen[0].x - screen[2].x) * (touch[1].y - touch[2].y)) - ((screen[1].x - screen[2].x) * (touch[0].y - touch[2].y))) / delta,
      .betaX = (((touch[0].x - touch[2].x) * (screen[1].x - screen[2].x)) - ((touch[1].x - touch[2].x) * (screen[0].x - screen[2].x))) / delta,
      .deltaX = ((screen[0].x * ((touch[1].x * touch[2].y) - (touch[2].x * touch[1].y))) - (screen[1].x * ((touch[0].x * touch[2].y) - (touch[2].x * touch[0].y))) + (screen[2].x * ((touch[0].x * touch[1].y) - (touch[1].x * touch[0].y)))) / delta,
      .alphaY = (((screen[0].y - screen[2].y) * (touch[1].y - touch[2].y)) - ((screen[1].y - screen[2].y) * (touch[0].y - touch[2].y))) / delta,
      .betaY = (((touch[0].x - touch[2].x) * (screen[1].y - screen[2].y)) - ((touch[1].x - touch[2].x) * (screen[0].y - screen[2].y))) / delta,
      .deltaY = ((screen[0].y * (touch[1].x * touch[2].y - touch[2].x * touch[1].y)) - (screen[1].y * (touch[0].x * touch[2].y - touch[2].x * touch[0].y)) + (screen[2].y * (touch[0].x * touch[1].y - touch[1].x * touch[0].y))) / delta,
  };
}
#endif

#ifndef DISPLAY_SOFTWARE_ROTATION
static void lvgl_display_resolution_changed_callback(lv_event_t *event)
{
  lv_display_t *display = static_cast<lv_display_t *>(event->user_data); // pass display via user_data
  const esp_lcd_panel_handle_t panel_handle = (esp_lcd_panel_handle_t)display->user_data;
  switch (lv_display_get_rotation(display))
  {
  case LV_DISPLAY_ROTATION_0:
    ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(panel_handle, DISPLAY_SWAP_XY));
    ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel_handle, DISPLAY_MIRROR_X, DISPLAY_MIRROR_Y));
    break;
  case LV_DISPLAY_ROTATION_90:
    ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(panel_handle, !DISPLAY_SWAP_XY));
    ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel_handle, DISPLAY_MIRROR_X, !DISPLAY_MIRROR_Y));
    break;
  case LV_DISPLAY_ROTATION_180:
    ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(panel_handle, DISPLAY_SWAP_XY));
    ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel_handle, !DISPLAY_MIRROR_X, !DISPLAY_MIRROR_Y));
    break;
  case LV_DISPLAY_ROTATION_270:
    ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(panel_handle, !DISPLAY_SWAP_XY));
    ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel_handle, !DISPLAY_MIRROR_X, DISPLAY_MIRROR_Y));
    break;
  }
}
#endif

// ===== LvglDriver member functions =====

LvglDriver::LvglDriver() { init(); }

void LvglDriver::init()
{
  if (display_) return; // already initialized
  log_d("LvglDriver::init");

#if LV_USE_LOG
  lv_log_register_print_cb(lvgl_log);
#endif

  lv_init();

  // Binary backlight (no PWM). Adjust polarity if needed (HIGH=on assumed now).
  pinMode(GPIO_BCKL, OUTPUT);
  digitalWrite(GPIO_BCKL, HIGH);

  display_ = lvgl_lcd_init();

#ifndef DISPLAY_SOFTWARE_ROTATION
  lv_display_add_event_cb(display_, lvgl_display_resolution_changed_callback, LV_EVENT_RESOLUTION_CHANGED, display_);
#endif

  lv_obj_clean(lv_screen_active());
  // Test box to verify drawing
  lv_obj_t *box = lv_obj_create(lv_screen_active());
  lv_obj_set_size(box, 120, 120);
  lv_obj_center(box);
  lv_obj_set_style_bg_color(box, lv_color_hex(0x0000FF), 0);
  lv_obj_set_style_bg_opa(box, LV_OPA_COVER, 0);

#ifdef BOARD_HAS_TOUCH
  indev_ = lvgl_touch_init();
  lv_indev_set_disp(indev_, display_);
  driver_touch_read_cb = lv_indev_get_read_cb(indev_);
  lv_indev_set_read_cb(indev_, lvgl_touch_calibration_transform);
  lv_indev_enable(indev_, true);
  s_lvgl_driver_instance = this;
#endif
}

void LvglDriver::setRotation(lv_display_rotation_t rotation)
{
  if (!display_) return;
  lv_display_set_rotation(display_, rotation);
}

void LvglDriver::setBacklight(bool on)
{
  pinMode(GPIO_BCKL, OUTPUT);
  digitalWrite(GPIO_BCKL, on ? HIGH : LOW);
}

// Singleton accessor
LvglDriver &lvgl_driver()
{
  static LvglDriver instance;
  #ifdef BOARD_HAS_TOUCH
  s_lvgl_driver_instance = &instance;
  #endif
  return instance;
}
