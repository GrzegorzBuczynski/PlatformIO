#include <Arduino.h>
#include "driver/lvgl_driver.h"
#include <ui/ui.h>
#include "screen_rotation/screen_rotation.hpp"
#include "ui/components/qr_code.h"

static LvglDriver driver;

void setup()
{
#ifdef ARDUINO_USB_CDC_ON_BOOT
    delay(5000);
#endif
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    log_i("Board: %s", BOARD_NAME);
    log_i("CPU: %s rev%d, CPU Freq: %d Mhz, %d core(s)", ESP.getChipModel(), ESP.getChipRevision(), getCpuFrequencyMhz(), ESP.getChipCores());
    log_i("Free heap: %d bytes", ESP.getFreeHeap());
    log_i("Free PSRAM: %d bytes", ESP.getPsramSize());
    log_i("SDK version: %s", ESP.getSdkVersion());

    // Create driver instance (initializes LVGL + hardware)
    driver.init();
    driver.setRotation(LV_DISPLAY_ROTATION_180);
    ui_init();
    // To use third party libraries, enable the define in lv_conf.h: #define LV_USE_QRCODE 1
    // const char *qr_data = "https://github.com/rzeldent/esp32-smartdisplay";
    const char *qr_data = "https://github.com/GrzegorzBuczynski";
    createQRCode(qr_data);
}

ulong next_millis;
auto lv_last_tick = millis();

void loop()
{
    auto const now = millis();
    if (now > next_millis)
    {
        next_millis = now + 500;
        char text_buffer[32];
        sprintf(text_buffer, "%lu", now);
        lv_label_set_text(ui_lblMillisecondsValue, text_buffer);
    }
    // Update the ticker
    lv_tick_inc(now - lv_last_tick);
    lv_last_tick = now;
    // Update the UI
    lv_timer_handler();
}