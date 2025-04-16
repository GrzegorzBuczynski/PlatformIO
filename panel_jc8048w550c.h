#pragma once


#define LCD_WIDTH 800
#define LCD_HEIGHT 480

#define RGB_DATA_WIDTH        16 
#define RGB_HSYNC_POLARITY    0
#define RGB_VSYNC_POLARITY    0
#define RGB_DE_POLARITY       0
#define RGB_PIXEL_CLOCK_HZ    (10 * 1000 * 1000)  // możesz później sprawdzić też 10 MHz

#define GPIO_BCKL           21
#define DISPLAY_SWAP_XY     0
#define DISPLAY_MIRROR_X    0
#define DISPLAY_MIRROR_Y    0

// --- Synchronizacja
#define PIN_NUM_HSYNC         39
#define PIN_NUM_VSYNC         41
#define PIN_NUM_DE            40
#define PIN_NUM_PCLK          42

// --- Dane RGB (18-bit)
#define PIN_NUM_DATA0         8     // DB1(B)
#define PIN_NUM_DATA1         3     // DB2(B)
#define PIN_NUM_DATA2         46    // DB3(B)
#define PIN_NUM_DATA3         9     // DB4(B)
#define PIN_NUM_DATA4         1     // DB5(B)
#define PIN_NUM_DATA5         6     // DB7(G)  – brak DB6(G) w tabeli
#define PIN_NUM_DATA6         5     // DB6(G)
#define PIN_NUM_DATA7         7     // DB8(G)
#define PIN_NUM_DATA8         15    // DB9(G)
#define PIN_NUM_DATA9         16    // DB10(G)
#define PIN_NUM_DATA10        4     // DB11(G)
#define PIN_NUM_DATA11        45    // DB13(R) (brak DB12)
#define PIN_NUM_DATA12        48    // DB14(R)
#define PIN_NUM_DATA13        47    // DB15(R)
#define PIN_NUM_DATA14        21    // DB16(R)
#define PIN_NUM_DATA15        14    // DB17(R)
#define PIN_NUM_DATA16        -1
#define PIN_NUM_DATA17        -1

// --- Podświetlenie
#define PIN_NUM_BK_LIGHT      21  // BL_C
#define PIN_NUM_DISP_EN       -1

// --- Dotyk
#define PIN_NUM_TOUCH_INT     -1
#define PIN_NUM_TOUCH_RST     -1

#define I2C_TOUCH_PORT        0
#define I2C_TOUCH_SDA         19  // TP_SDA
#define I2C_TOUCH_SCL         20  // TP_SCL
#define TOUCH_I2C_ADDR        0x38
