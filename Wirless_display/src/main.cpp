#include <Arduino.h>
#include <esp32_smartdisplay.h>
#include <time.h>
#include <WiFi.h>
#include "config.h"
#include "parent_control.h"
#include <EEPROM.h>


#define EEPROM_SIZE 512
#define MAX_DATA_LEN 256

int flag = 0;

const char *ssid_default = "Domowa_Siec";
const char *password_default = "Twoje_Haslo";

String ssid;
String password;
char receivedData[MAX_DATA_LEN] = {0};
uint8_t buffer[(DISPLAY_WIDTH * 3) + 1];

WiFiServer server(80);




void connectToWiFi()
{
  WiFi.begin(ssid.c_str(), password.c_str());
  Serial.print("Łączenie z ");
  Serial.println(ssid);
  auto time = 0;

  while (WiFi.status() != WL_CONNECTED && time < 10000)
  {
    delay(500);
    time += 500;
    Serial.print(".");
  }

  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Nie można połączyć się z siecią WiFi!");
    return;
  }
  Serial.println("\nPołączono z siecią WiFi!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}



lv_color_t cbuf[DISPLAY_WIDTH * DISPLAY_HEIGHT];
lv_obj_t * canvas = lv_canvas_create(lv_scr_act());
// lv_canvas_set_buffer(canvas, cbuf, DISPLAY_WIDTH, DISPLAY_HEIGHT, LV_IMG_CF_TRUE_COLOR);

// Załóżmy, że masz bufor z danymi o szerokości DISPLAY_WIDTH i formacie RGB888
void draw_line(uint8_t *buffer, uint16_t y) {
    for (uint16_t x = 0; x < DISPLAY_WIDTH; x++) {
        uint8_t r = buffer[x * 3 + 0];
        uint8_t g = buffer[x * 3 + 1];
        uint8_t b = buffer[x * 3 + 2];
        lv_color_t color = lv_color_make(r, g, b);
        lv_canvas_set_px(canvas, x, y, color, LV_OPA_COVER);
    }
}

uint16_t line = 0;

void handleClientConnection()
{
  WiFiClient client = server.available();
  if (client)
  {
    Serial.println("Nowy klient!");

    while (client.connected())
    {
      if (client.available())
      {
        size_t len = client.readBytes(buffer, sizeof(buffer));
        if (len > 0)
        {
            draw_line(buffer, line); // funkcja z przykładu wyżej
            line++;
        }
        if (line >= DISPLAY_HEIGHT)
        {
          line = 0;
          lv_obj_invalidate(canvas); // odśwież canvas
        }
        // NIE zamykaj połączenia tutaj!
      }
      delay(1); // nie blokuj CPU
    }
    Serial.println("Klient się rozłączył.");
  }
}


void handleSerialInput()
{
  if (Serial.available())
  {
    String input = Serial.readStringUntil('\n');
    input.trim(); // Usuń białe znaki z początku i końca

    if (input.startsWith("SSID:"))
    {
      ssid = input.substring(5);
      EEPROM.put(0, ssid);
      EEPROM.commit();
      Serial.println("Zapisano nowy SSID!");
    }
    else if (input.startsWith("PASS:"))
    {
      password = input.substring(5);
      EEPROM.put(sizeof(String), password);
      EEPROM.commit();
      Serial.println("Zapisano nowe hasło!");
    }
  }
}

void setup()
{
  Serial.begin(115200);
  EEPROM.begin(EEPROM_SIZE);

  // Wczytaj dane z EEPROM
  EEPROM.get(0, ssid);
  EEPROM.get(sizeof(String), password);

  // Jeśli EEPROM pusty, użyj domyślnych wartości
  if (ssid.length() == 0 || password.length() == 0)
  {
    ssid = ssid_default;
    password = password_default;
  }

  connectToWiFi();
  if (WiFi.status() == WL_CONNECTED)
  {
    server.begin();
    Serial.println("Serwer uruchomiony!");
  }
}
void displayLoop()
{
  while (flag == 1 && WiFi.status() == WL_CONNECTED)
  {
    handleClientConnection();
  }
}

void loop()
{
  if (WiFi.status() != WL_CONNECTED)
    connectToWiFi();
  displayLoop();
}

