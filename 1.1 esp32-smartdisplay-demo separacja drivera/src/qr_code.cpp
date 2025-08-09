#include "qr_code.h"
#include <ui/ui.h>
#include <string.h>

void createQRCode(const char *data)
{
    auto qr = lv_qrcode_create(ui_scrMain);
    lv_qrcode_set_size(qr, 100);
    lv_qrcode_set_light_color(qr, lv_color_white());
    lv_qrcode_set_dark_color(qr, lv_color_black());
    lv_qrcode_update(qr, data, strlen(data));
    lv_obj_center(qr);
}
