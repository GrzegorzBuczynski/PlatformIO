#include "ScreenParams.hpp"
#include "Colors.hpp"
#include <Arduino.h>
#include "GBUButton.hpp"

ButtonLayout getButtonLayout(uint8_t viewMode) {
    ButtonLayout layout;
      
      if (viewMode == PORTRAIT) { // Portrait (pionowy)
          layout.btnRadio   = (GBUButton){ 
              static_cast<int>(SCREEN_WIDTH_PORTRAIT * 0.05), 
              static_cast<int>(SCREEN_HEIGHT_PORTRAIT * 0.10), 
              static_cast<int>(SCREEN_WIDTH_PORTRAIT * 0.4), 
              50, 
              "RADIO", 
              RED 
          };
          layout.btnNavi    = (GBUButton){ 
              static_cast<int>(SCREEN_WIDTH_PORTRAIT * 0.55), 
              static_cast<int>(SCREEN_HEIGHT_PORTRAIT * 0.10), 
              static_cast<int>(SCREEN_WIDTH_PORTRAIT * 0.4), 
              50, 
              "NAVI", 
              BLUE 
          };
          layout.btnParams  = (GBUButton){ 
              static_cast<int>(SCREEN_WIDTH_PORTRAIT * 0.3), 
              static_cast<int>(SCREEN_HEIGHT_PORTRAIT * 0.35), 
              static_cast<int>(SCREEN_WIDTH_PORTRAIT * 0.4), 
              50, 
              "PARAMS", 
              GREEN 
          };
          layout.btnCamera  = (GBUButton){ 
              static_cast<int>(SCREEN_WIDTH_PORTRAIT * 0.2), 
              static_cast<int>(SCREEN_HEIGHT_PORTRAIT * 0.65), 
              static_cast<int>(SCREEN_WIDTH_PORTRAIT * 0.6), 
              50, 
              "KAMERA", 
              YELLOW 
          };
          layout.btnBack    = (GBUButton){ 
              static_cast<int>(SCREEN_WIDTH_PORTRAIT * 0.02), 
              static_cast<int>(SCREEN_HEIGHT_PORTRAIT * 0.02), 
              static_cast<int>(SCREEN_WIDTH_PORTRAIT * 0.2), 
              static_cast<int>(SCREEN_HEIGHT_PORTRAIT * 0.15), 
              "<--", 
              CYAN 
          };
      /////////////////////////////////////////////////////////////////////////////////
      } else { // Landscape (poziomy)
          layout.btnRadio   = (GBUButton){ 
              static_cast<int>(SCREEN_WIDTH_LANDSCAPE * 0.10), 
              static_cast<int>(SCREEN_HEIGHT_LANDSCAPE * 0.15), 
              static_cast<int>(SCREEN_WIDTH_LANDSCAPE * 0.35), 
              50, 
              "RADIO", 
              RED 
          };
          layout.btnNavi    = (GBUButton){ 
              static_cast<int>(SCREEN_WIDTH_LANDSCAPE * 0.10), 
              static_cast<int>(SCREEN_HEIGHT_LANDSCAPE * 0.65), 
              static_cast<int>(SCREEN_WIDTH_LANDSCAPE * 0.35), 
              50, 
              "NAVI", 
              BLUE 
          };
          layout.btnParams  = (GBUButton){ 
              static_cast<int>(SCREEN_WIDTH_LANDSCAPE * 0.55), 
              static_cast<int>(SCREEN_HEIGHT_LANDSCAPE * 0.15), 
              static_cast<int>(SCREEN_WIDTH_LANDSCAPE * 0.35), 
              50, 
              "PARAMS", 
              GREEN 
          };
          layout.btnCamera  = (GBUButton){ 
              static_cast<int>(SCREEN_WIDTH_LANDSCAPE * 0.55), 
              static_cast<int>(SCREEN_HEIGHT_LANDSCAPE * 0.65), 
              static_cast<int>(SCREEN_WIDTH_LANDSCAPE * 0.35), 
              50, 
              "KAMERA", 
              YELLOW 
          };
          layout.btnBack    = (GBUButton){ 
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
