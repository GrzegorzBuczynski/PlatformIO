#include <Arduino.h>

#include <esp32_smartdisplay.h>
#include <ui/ui.h>
#include "screen_rotation.h"
#include "qr_code.h"

void OnAddOneClicked(lv_event_t *e)
{
    static uint32_t cnt = 0;
    cnt++;
    lv_label_set_text_fmt(ui_lblCountValue, "%u", cnt);
}

void OnRotateClicked(lv_event_t *e)
{
    // Użyj wyizolowanej funkcji z modułu screen_rotation
    rotate_screen_to_next_orientation(e);
}

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

    smartdisplay_init();

    __attribute__((unused)) auto disp = lv_disp_get_default();
    // lv_disp_set_rotation(disp, LV_DISP_ROT_90);
    // lv_disp_set_rotation(disp, LV_DISP_ROT_180);
    // lv_disp_set_rotation(disp, LV_DISP_ROT_270);

    ui_init();

    // To use third party libraries, enable the define in lv_conf.h: #define LV_USE_QRCODE 1
    const char *qr_data = "https://github.com/rzeldent/esp32-smartdisplay";
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

#ifdef BOARD_HAS_RGB_LED
        auto const rgb = (now / 2000) % 8;
        smartdisplay_led_set_rgb(rgb & 0x01, rgb & 0x02, rgb & 0x04);
#endif

#ifdef BOARD_HAS_CDS
        auto cdr = analogReadMilliVolts(CDS);
        sprintf(text_buffer, "%d", cdr);
        lv_label_set_text(ui_lblCdrValue, text_buffer);
#endif
    }

    // Update the ticker
    lv_tick_inc(now - lv_last_tick);
    lv_last_tick = now;
    // Update the UI
    lv_timer_handler();
}