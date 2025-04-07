#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include <Adafruit_GFX.h>
#include "Colors.hpp"

// TFT i dotyk
MCUFRIEND_kbv tft;


#define SCREEN_WIDTH_LANDSCAPE  400
#define SCREEN_HEIGHT_LANDSCAPE 240

#define SCREEN_WIDTH_PORTRAIT  240
#define SCREEN_HEIGHT_PORTRAIT 400

#define PORTRAIT 0
#define LANDSCAPE 1

#define VIEW_MODE LANDSCAPE


// TouchScreen piny Mega
#define YP A1  // Must be an analog pin
#define XM A2  // Must be an analog pin
#define YM 7
#define XP 6

// Kalibracja (możesz zmienić po testach)
#define TS_MINX 120
#define TS_MAXX 900
#define TS_MINY 70
#define TS_MAXY 920

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
TSPoint tp;

#define MINPRESSURE 200
#define MAXPRESSURE 1000

// Ekran GUI
enum Screen { MAIN_MENU, RADIO, NAVI, PARAMS, CAMERA };
Screen currentScreen = MAIN_MENU;

// --- Przyciski (koordynaty) ---
struct Button {
  int x, y, w, h;
  const char* label;
  uint16_t color;
};

void debugButton(Button btn) {
  Serial.print("Button label: "); Serial.println(btn.label);
  Serial.print("Button x: "); Serial.println(btn.x);
  Serial.print("Button y: "); Serial.println(btn.y);
  Serial.print("Button w: "); Serial.println(btn.w);
  Serial.print("Button h: "); Serial.println(btn.h);
  Serial.print("Button color: "); Serial.println(btn.color, HEX);
}

// int screenW;
// int screenH;

int screenW = tft.width();
int screenH = tft.height();


typedef struct {
  Button btnRadio;
  Button btnNavi;
  Button btnParams;
  Button btnCamera;
  Button btnBack;
} ButtonLayout;

// poor layout, not acceptable for now
// ButtonLayout getButtonLayout(uint8_t viewMode) {
//   ButtonLayout layout;
  
//   if (viewMode == 0) { // Portrait (pionowy) - dla ekranu 432x240
//       // Przycisk Back w lewym górnym rogu, ale mniejszy aby nie nachodził na inne
//       layout.btnBack    = (Button){ 10, 10, 80, 40, "<--", CYAN };
      
//       // Przyciski w pierwszym rzędzie - odsunięte od lewej krawędzi i od przycisku Back
//       layout.btnRadio   = (Button){ 110, 30, 150, 50, "RADIO", RED };
//       layout.btnNavi    = (Button){ 270, 30, 150, 50, "NAVI", BLUE };
      
//       // Przycisk w środkowym rzędzie
//       layout.btnParams  = (Button){ 140, 100, 150, 50, "PARAMS", GREEN };
      
//       // Przycisk w dolnym rzędzie
//       layout.btnCamera  = (Button){ 110, 170, 210, 50, "KAMERA", YELLOW };
//   } else { // Landscape (poziomy) - dla ekranu 432x240
//       // Lewa strona ekranu
//       layout.btnBack    = (Button){ 10, 10, 80, 40, "<--", CYAN };
//       layout.btnRadio   = (Button){ 30, 70, 170, 50, "RADIO", RED };
//       layout.btnNavi    = (Button){ 30, 140, 170, 50, "NAVI", BLUE };
      
//       // Prawa strona ekranu
//       layout.btnParams  = (Button){ 230, 70, 170, 50, "PARAMS", GREEN };
//       layout.btnCamera  = (Button){ 230, 140, 170, 50, "KAMERA", YELLOW };
//   }
  
//   return layout;
// }



ButtonLayout getButtonLayout(uint8_t viewMode) {
  ButtonLayout layout;
  
  if (viewMode == PORTRAIT) { // Portrait (pionowy)
      layout.btnRadio   = (Button){ 
          static_cast<int>(SCREEN_WIDTH_PORTRAIT * 0.05), 
          static_cast<int>(SCREEN_HEIGHT_PORTRAIT * 0.10), 
          static_cast<int>(SCREEN_WIDTH_PORTRAIT * 0.4), 
          50, 
          "RADIO", 
          RED 
      };
      layout.btnNavi    = (Button){ 
          static_cast<int>(SCREEN_WIDTH_PORTRAIT * 0.55), 
          static_cast<int>(SCREEN_HEIGHT_PORTRAIT * 0.10), 
          static_cast<int>(SCREEN_WIDTH_PORTRAIT * 0.4), 
          50, 
          "NAVI", 
          BLUE 
      };
      layout.btnParams  = (Button){ 
          static_cast<int>(SCREEN_WIDTH_PORTRAIT * 0.3), 
          static_cast<int>(SCREEN_HEIGHT_PORTRAIT * 0.35), 
          static_cast<int>(SCREEN_WIDTH_PORTRAIT * 0.4), 
          50, 
          "PARAMS", 
          GREEN 
      };
      layout.btnCamera  = (Button){ 
          static_cast<int>(SCREEN_WIDTH_PORTRAIT * 0.2), 
          static_cast<int>(SCREEN_HEIGHT_PORTRAIT * 0.65), 
          static_cast<int>(SCREEN_WIDTH_PORTRAIT * 0.6), 
          50, 
          "KAMERA", 
          YELLOW 
      };
      layout.btnBack    = (Button){ 
          static_cast<int>(SCREEN_WIDTH_PORTRAIT * 0.02), 
          static_cast<int>(SCREEN_HEIGHT_PORTRAIT * 0.02), 
          static_cast<int>(SCREEN_WIDTH_PORTRAIT * 0.2), 
          static_cast<int>(SCREEN_HEIGHT_PORTRAIT * 0.15), 
          "<--", 
          CYAN 
      };
  /////////////////////////////////////////////////////////////////////////////////
  } else { // Landscape (poziomy)
      layout.btnRadio   = (Button){ 
          static_cast<int>(SCREEN_WIDTH_LANDSCAPE * 0.10), 
          static_cast<int>(SCREEN_HEIGHT_LANDSCAPE * 0.15), 
          static_cast<int>(SCREEN_WIDTH_LANDSCAPE * 0.35), 
          50, 
          "RADIO", 
          RED 
      };
      layout.btnNavi    = (Button){ 
          static_cast<int>(SCREEN_WIDTH_LANDSCAPE * 0.10), 
          static_cast<int>(SCREEN_HEIGHT_LANDSCAPE * 0.65), 
          static_cast<int>(SCREEN_WIDTH_LANDSCAPE * 0.35), 
          50, 
          "NAVI", 
          BLUE 
      };
      layout.btnParams  = (Button){ 
          static_cast<int>(SCREEN_WIDTH_LANDSCAPE * 0.55), 
          static_cast<int>(SCREEN_HEIGHT_LANDSCAPE * 0.15), 
          static_cast<int>(SCREEN_WIDTH_LANDSCAPE * 0.35), 
          50, 
          "PARAMS", 
          GREEN 
      };
      layout.btnCamera  = (Button){ 
          static_cast<int>(SCREEN_WIDTH_LANDSCAPE * 0.55), 
          static_cast<int>(SCREEN_HEIGHT_LANDSCAPE * 0.65), 
          static_cast<int>(SCREEN_WIDTH_LANDSCAPE * 0.35), 
          50, 
          "KAMERA", 
          YELLOW 
      };
      layout.btnBack    = (Button){ 
          static_cast<int>(SCREEN_WIDTH_LANDSCAPE * 0.02), 
          static_cast<int>(SCREEN_HEIGHT_LANDSCAPE * 0.02), 
          static_cast<int>(SCREEN_WIDTH_LANDSCAPE * 0.15), 
          static_cast<int>(SCREEN_HEIGHT_LANDSCAPE * 0.2), 
          "<--", 
          CYAN 
      };
  }
  
  return layout;
}

// //not optimal layout, but works for now
// ButtonLayout getButtonLayout(uint8_t viewMode) {
//   ButtonLayout layout;
  
//   if (viewMode == 0) { // Portrait (pionowy)
//       layout.btnRadio   = (Button){ screenW * 0.05, screenH * 0.10, screenW * 0.4, 50, "RADIO", RED };
//       layout.btnNavi    = (Button){ screenW * 0.55, screenH * 0.10, screenW * 0.4, 50, "NAVI", BLUE };
//       layout.btnParams  = (Button){ screenW * 0.3,  screenH * 0.35, screenW * 0.4, 50, "PARAMS", GREEN };
//       layout.btnCamera  = (Button){ screenW * 0.2,  screenH * 0.65, screenW * 0.6, 50, "KAMERA", YELLOW };
//       layout.btnBack    = (Button){ screenW * 0.02, screenH * 0.02, screenW * 0.2, screenH * 0.15, "<--", CYAN };
//   } else { // Landscape (poziomy)
//       layout.btnRadio   = (Button){ screenW * 0.10, screenH * 0.05, screenW * 0.35, 50, "RADIO", RED };
//       layout.btnNavi    = (Button){ screenW * 0.10, screenH * 0.55, screenW * 0.35, 50, "NAVI", BLUE };
//       layout.btnParams  = (Button){ screenW * 0.55, screenH * 0.05, screenW * 0.35, 50, "PARAMS", GREEN };
//       layout.btnCamera  = (Button){ screenW * 0.55, screenH * 0.55, screenW * 0.35, 50, "KAMERA", YELLOW };
//       layout.btnBack    = (Button){ screenW * 0.02, screenH * 0.02, screenW * 0.15, screenH * 0.2, "<--", CYAN };
//   }
  
//   return layout;
// }

// //portrait = (screenW < screenH); // true if portrait mode setRotation(0);
// Button btnRadio   = { screenW * 0.05, screenH * 0.10, screenW * 0.4, 50, "RADIO", RED };
// Button btnNavi    = { screenW * 0.55, screenH * 0.10, screenW * 0.4, 50, "NAVI", BLUE };
// Button btnParams  = { screenW * 0.3,  screenH * 0.35, screenW * 0.4, 50, "PARAMS", GREEN };
// Button btnCamera  = { screenW * 0.2,  screenH * 0.65, screenW * 0.6, 50, "KAMERA", YELLOW };
// Button btnBack    = { screenW * 0.02, screenH * 0.02, screenW * 0.2, screenH * 0.15, "<--", CYAN };



// Button btnRadio   = { 20, 40, 120, 60, "RADIO", RED };
// Button btnNavi    = { 180, 40, 120, 60, "NAVI", BLUE };
// Button btnParams  = { 100, 120, 120, 60, "PARAMS", GREEN };
// Button btnCamera  = { 60, 200, 200, 60, "KAMERA", YELLOW };
// Button btnBack    = { 10, 10, 80, 40, "<--", CYAN };

void drawButton(Button btn) {
  tft.fillRect(btn.x, btn.y, btn.w, btn.h, btn.color);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  int textW = strlen(btn.label) * 12;  // oszacowanie szerokości (2x6px)
  int cx = btn.x + (btn.w - textW) / 2;
  int cy = btn.y + (btn.h - 16) / 2;
  tft.setCursor(cx, cy);
  tft.print(btn.label);
}


// // --- Funkcje pomocnicze ---
// void drawButton(Button btn) {
//   tft.fillRect(btn.x, btn.y, btn.w, btn.h, btn.color);
//   tft.setTextColor(WHITE);
//   tft.setTextSize(2);
//   int cx = btn.x + (btn.w / 2) - (strlen(btn.label) * 6); // prosta centrowanie
//   int cy = btn.y + (btn.h / 2) - 8;
//   tft.setCursor(cx, cy);
//   tft.print(btn.label);
// }



bool isPressed(Button btn, int x, int y) {
  return (x > btn.x && x < (btn.x + btn.w) &&
          y > btn.y && y < (btn.y + btn.h));
}

TSPoint getTouch() {
  TSPoint p = ts.getPoint();
  pinMode(YP, OUTPUT);
  pinMode(XM, OUTPUT);
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    int x = map(p.y, TS_MINY, TS_MAXY, 0, tft.width());
    int y = map(p.x, TS_MINX, TS_MAXX, 0, tft.height());
    return TSPoint(x, y, 1);
  }
  return TSPoint(-1, -1, 0);
}

// #define VIEW_MODE_LANDSCAPE 1

// Dodaj to na poziomie globalnym
ButtonLayout currentLayout;

void updateLayout() {
  currentLayout = getButtonLayout(VIEW_MODE);
}

void drawMainMenu() {
  tft.fillScreen(BLACK);
  
  // Aktualizacja layoutu przed użyciem
  updateLayout();

  drawButton(currentLayout.btnRadio);
  drawButton(currentLayout.btnNavi);
  drawButton(currentLayout.btnParams);
  drawButton(currentLayout.btnCamera);
  drawButton(currentLayout.btnBack);
  debugButton(currentLayout.btnRadio); 
  debugButton(currentLayout.btnNavi);
  debugButton(currentLayout.btnParams);
  debugButton(currentLayout.btnCamera);
  debugButton(currentLayout.btnBack);
}

void drawRadioScreen() {
  tft.fillScreen(DARKGREY);
  drawButton(currentLayout.btnBack);  // Używamy currentLayout zamiast lokalnej zmiennej
  tft.setCursor(100, 100);
  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.print("RADIO 99.8 MHz");
}

void drawNaviScreen() {
  tft.fillScreen(BLUE);
  drawButton(currentLayout.btnBack);  // Poprawiona zmienna z btnBack na currentLayout.btnBack
  tft.setCursor(60, 100);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("Nawigacja demo");
}

void drawParamsScreen() {
  tft.fillScreen(BLACK);
  drawButton(currentLayout.btnBack);  // Poprawiona zmienna z btnBack na currentLayout.btnBack
  tft.setCursor(60, 100);
  tft.setTextSize(2);
  tft.setTextColor(GREEN);
  tft.print("Temp: 90C");
  tft.setCursor(60, 130);
  tft.print("RPM: 2500");
}

void drawCameraScreen() {
  tft.fillScreen(BLACK);
  drawButton(currentLayout.btnBack);  // Poprawiona zmienna z btnBack na currentLayout.btnBack
  tft.setCursor(60, 100);
  tft.setTextSize(2);
  tft.setTextColor(YELLOW);
  tft.print("Kamera niedostepna");
  tft.setCursor(60, 130);
  tft.print("Dostepna na ESP32");
}

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
  tp = getTouch();
  if (tp.z > 0) {
    switch (currentScreen) {
      case MAIN_MENU:
        if (isPressed(currentLayout.btnRadio, tp.x, tp.y)) {
          currentScreen = RADIO;
          drawRadioScreen();
        } else if (isPressed(currentLayout.btnNavi, tp.x, tp.y)) {
          currentScreen = NAVI;
          drawNaviScreen();
        } else if (isPressed(currentLayout.btnParams, tp.x, tp.y)) {
          currentScreen = PARAMS;
          drawParamsScreen();
        } else if (isPressed(currentLayout.btnCamera, tp.x, tp.y)) {
          currentScreen = CAMERA;
          drawCameraScreen();
        }
        break;

      case RADIO:
      case NAVI:
      case PARAMS:
      case CAMERA:
        if (isPressed(currentLayout.btnBack, tp.x, tp.y)) {
          currentScreen = MAIN_MENU;
          drawMainMenu();
        }
        break;
    }
    delay(300); // debouncing
  }
}
