#ifndef QR_CODE_H
#define QR_CODE_H

#include <lvgl.h>
#include "../ui.h"
#include <string.h>

/**
 * @brief Creates a QR code widget
 * @param data The data to encode in the QR code
 */
void createQRCode(const char *data);

#endif // QR_CODE_H
