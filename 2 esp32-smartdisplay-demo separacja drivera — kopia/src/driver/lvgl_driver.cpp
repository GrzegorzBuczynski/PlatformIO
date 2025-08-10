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

// Local state for extended features (kept separate from core library implementation)
static lv_display_t *display = nullptr;
#ifdef BOARD_HAS_TOUCH
static lv_indev_t *indev = nullptr;
lvgl_touch_calibration_data_t lvgl_touch_calibration_data;
static void (*driver_touch_read_cb)(lv_indev_t *indev, lv_indev_data_t *data) = nullptr;
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
  if (lvgl_touch_calibration_data.valid && data->state == LV_INDEV_STATE_PRESSED)
  {
    lv_point_t pt = {
        .x = (int32_t)roundf(data->point.x * lvgl_touch_calibration_data.alphaX + data->point.y * lvgl_touch_calibration_data.betaX + lvgl_touch_calibration_data.deltaX),
        .y = (int32_t)roundf(data->point.x * lvgl_touch_calibration_data.alphaY + data->point.y * lvgl_touch_calibration_data.betaY + lvgl_touch_calibration_data.deltaY)};
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
  const esp_lcd_panel_handle_t panel_handle = (esp_lcd_panel_handle_t)display->user_data;
  switch (lv_display_get_rotation(display))
  {
  case LV_DISP_ROT_0:
    ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(panel_handle, DISPLAY_SWAP_XY));
    ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel_handle, DISPLAY_MIRROR_X, DISPLAY_MIRROR_Y));
    break;
  case LV_DISP_ROT_90:
    ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(panel_handle, !DISPLAY_SWAP_XY));
    ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel_handle, DISPLAY_MIRROR_X, !DISPLAY_MIRROR_Y));
    break;
  case LV_DISP_ROT_180:
    ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(panel_handle, DISPLAY_SWAP_XY));
    ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel_handle, !DISPLAY_MIRROR_X, !DISPLAY_MIRROR_Y));
    break;
  case LV_DISP_ROT_270:
    ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(panel_handle, !DISPLAY_SWAP_XY));
    ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel_handle, !DISPLAY_MIRROR_X, DISPLAY_MIRROR_Y));
    break;
  }
}
#endif

void lvgl_driver_init()
{
  log_d("lvgl_driver_init");
#ifdef BOARD_HAS_RGB_LED
  // RGB LED initialization handled by library (avoid duplicate)
#endif

#ifdef BOARD_HAS_CDS
  // Adaptive brightness handled by library
#endif

#ifdef BOARD_HAS_SPEAK
  // Speaker setup handled by library
#endif

#if LV_USE_LOG
  lv_log_register_print_cb(lvgl_log);
#endif

  lv_init();

  // Binary backlight (no PWM). Adjust polarity if needed (HIGH=on assumed now).
  pinMode(GPIO_BCKL, OUTPUT);
  digitalWrite(GPIO_BCKL, HIGH);

  display = lvgl_lcd_init();

#ifndef DISPLAY_SOFTWARE_ROTATION
  lv_display_add_event_cb(display, lvgl_display_resolution_changed_callback, LV_EVENT_RESOLUTION_CHANGED, NULL);
#endif

  lv_obj_clean(lv_screen_active());
  // Test box to verify drawing
  lv_obj_t *box = lv_obj_create(lv_screen_active());
  lv_obj_set_size(box, 120, 120);
  lv_obj_center(box);
  lv_obj_set_style_bg_color(box, lv_color_hex(0x0000FF), 0);
  lv_obj_set_style_bg_opa(box, LV_OPA_COVER, 0);

#ifdef BOARD_HAS_TOUCH
  indev = lvgl_touch_init();
  lv_indev_set_disp(indev, display);
  driver_touch_read_cb = lv_indev_get_read_cb(indev);
  lv_indev_set_read_cb(indev, lvgl_touch_calibration_transform);
  lv_indev_enable(indev, true);
#endif
}

void lvgl_backlight_set(bool on)
{
  digitalWrite(GPIO_BCKL, on ? HIGH : LOW);
}
