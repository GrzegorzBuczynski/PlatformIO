#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include <Adafruit_GFX.h>
#include "Colors.hpp"
#include "ScreenParams.hpp"
#include "Layout.hpp"
#include "GBUButton.hpp"




// TFT i dotyk
MCUFRIEND_kbv tft;

// TouchScreen piny Mega
#define YP A3  // Must be an analog pin
#define XM A2  // Must be an analog pin
#define YM 9
#define XP 8

// Kalibracja (możesz zmienić po testach)
#define TS_MINX 120
#define TS_MAXX 900
#define TS_MINY 70
#define TS_MAXY 920

const int TS_LEFT=882,TS_RT=155,TS_TOP=57,TS_BOT=928;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
TSPoint tp;

#define MINPRESSURE 200
#define MAXPRESSURE 1000

// Ekran GUI
enum Screen { MAIN_MENU, RADIO, NAVI, PARAMS, CAMERA };
Screen currentScreen = MAIN_MENU;

// void debugButton(Button btn) {
//   Serial.print("Button label: "); Serial.println(btn.label);
//   Serial.print("Button x: "); Serial.println(btn.x);
//   Serial.print("Button y: "); Serial.println(btn.y);
//   Serial.print("Button w: "); Serial.println(btn.w);
//   Serial.print("Button h: "); Serial.println(btn.h);
//   Serial.print("Button color: "); Serial.println(btn.color, HEX);
// }

int screenW = tft.width();
int screenH = tft.height();


bool isPressed(GBUButton btn, int x, int y) {
  return (x > btn.x && x < (btn.x + btn.w) &&
          y > btn.y && y < (btn.y + btn.h));
}

TSPoint getTouch() {
  TSPoint p = ts.getPoint();
  pinMode(YP, OUTPUT);
  pinMode(XM, OUTPUT);
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    int x = map(p.x, TS_LEFT, TS_RT, 0, tft.width());
    int y = map(p.y, TS_TOP, TS_BOT, 0, tft.height());
    return TSPoint(x, y, 1);
  }
  return TSPoint(-1, -1, 0);
}

GBUButton* currentLayout = nullptr;

const char* labels[] = {
  "<--",
  "RADIO",
  "NAVI",
  "PARAMS",
  "KAMERA",
  "USTAWIENIA",
  "INFO",
  "INNE",
  "TEST",
  NULL
};

uint16_t colors[] = {
  RED,
  BLUE,
  GREEN,
  YELLOW,
  CYAN,
  MAGENTA,
  ORANGE,
  GREEN,
  PURPLE
};



void updateLayout() {
  currentLayout = createButtonGrid(9, labels, colors);
}

void drawMainMenu() {
  tft.fillScreen(BLACK);
  updateLayout();
  GBUButton* btn = currentLayout;
  Serial.println("Drawing main menu...");
  while (btn != nullptr) {
    drawButton(*btn, tft);  // Używamy wskaźnika do przycisku
    btn = btn->next;
  }
}

// void drawRadioScreen() {
//   tft.fillScreen(DARKGREY);
//   drawButton(currentLayout.btnBack);  // Używamy currentLayout zamiast lokalnej zmiennej
//   tft.setCursor(100, 100);
//   tft.setTextSize(3);
//   tft.setTextColor(WHITE);
//   tft.print("RADIO 99.8 MHz");
// }

// void drawNaviScreen() {
//   tft.fillScreen(BLUE);
//   drawButton(currentLayout.btnBack);  // Poprawiona zmienna z btnBack na currentLayout.btnBack
//   tft.setCursor(60, 100);
//   tft.setTextSize(2);
//   tft.setTextColor(WHITE);
//   tft.print("Nawigacja demo");
// }

// void drawParamsScreen() {
//   tft.fillScreen(BLACK);
//   drawButton(currentLayout.btnBack);  // Poprawiona zmienna z btnBack na currentLayout.btnBack
//   tft.setCursor(60, 100);
//   tft.setTextSize(2);
//   tft.setTextColor(GREEN);
//   tft.print("Temp: 90C");
//   tft.setCursor(60, 130);
//   tft.print("RPM: 2500");
// }

// void drawCameraScreen() {
//   tft.fillScreen(BLACK);
//   drawButton(currentLayout.btnBack);  // Poprawiona zmienna z btnBack na currentLayout.btnBack
//   tft.setCursor(60, 100);
//   tft.setTextSize(2);
//   tft.setTextColor(YELLOW);
//   tft.print("Kamera niedostepna");
//   tft.setCursor(60, 130);
//   tft.print("Dostepna na ESP32");
// }

void setup() {
  Serial.begin(9600);
  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(VIEW_MODE);


  Serial.print("Screen width = ");
  Serial.println(screenW);
  Serial.print("Screen height = ");
  Serial.println(screenH);

  drawMainMenu();
}

void loop() {
  // tp = getTouch();
  // if (tp.z > 0) {
  //   switch (currentScreen) {
  //     case MAIN_MENU:
  //       if (isPressed(currentLayout.btnRadio, tp.x, tp.y)) {
  //         currentScreen = RADIO;
  //         drawRadioScreen();
  //       } else if (isPressed(currentLayout.btnNavi, tp.x, tp.y)) {
  //         currentScreen = NAVI;
  //         drawNaviScreen();
  //       } else if (isPressed(currentLayout.btnParams, tp.x, tp.y)) {
  //         currentScreen = PARAMS;
  //         drawParamsScreen();
  //       } else if (isPressed(currentLayout.btnCamera, tp.x, tp.y)) {
  //         currentScreen = CAMERA;
  //         drawCameraScreen();
  //       }
  //       break;

  //     case RADIO:
  //     case NAVI:
  //     case PARAMS:
  //     case CAMERA:
  //       if (isPressed(currentLayout.btnBack, tp.x, tp.y)) {
  //         currentScreen = MAIN_MENU;
  //         drawMainMenu();
  //       }
  //       break;
  //   }
    delay(300); // debouncing
  // }
}
