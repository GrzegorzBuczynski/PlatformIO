#include <Arduino.h>

#include <FastLED.h>

#define LED_PIN 48
#define NUM_LEDS 1

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50); // Ustaw jasność (opcjonalnie)
}

void loop() {
  // Ustaw diodę na czerwono
  // leds[0] = CRGB::Red;
  // FastLED.show();
  // delay(1000);

  // // Ustaw diodę na zielono
  // leds[0] = CRGB::Green;
  // FastLED.show();
  // delay(1000);

  // // Ustaw diodę na niebiesko
  // leds[0] = CRGB::Blue;
  // FastLED.show();
  // delay(1000);

  leds[0] = CRGB::Black;
  FastLED.show();
  delay(1000);
}

// void setup() {
//   // Ustaw pin GPIO36 jako wyjście
//   pinMode(48, OUTPUT);
//   pinMode(38, OUTPUT);
//   pinMode(36, OUTPUT);
//   pinMode(35, OUTPUT);
//   pinMode(20, OUTPUT);
//   pinMode(16, OUTPUT);
//   pinMode(0, OUTPUT);

//   // Ustaw stan pinu GPIO36 na niski (LOW)
//   digitalWrite(48, HIGH);
//   digitalWrite(38, LOW);
//   digitalWrite(36, LOW);
//   digitalWrite(35, LOW);
//   digitalWrite(20, LOW);
//   digitalWrite(16, LOW);
//   digitalWrite(0, LOW);
// }

// void loop() {
//   // Tutaj możesz umieścić dalszą logikę swojego programu
// }