#include <SD.h>
#include "ourOSObj.h"
#include <adafruit_1947_Obj.h>
#include <scr-een.h>

ourOSObj  ourOS;

void setup() {
   
   Serial.begin(57600);                                           //  Fire up serial for debugging.
   if (!initScreen(ADAFRUIT_1947,ADA_1947_SHIELD_CS,PORTRAIT)) {  // Init screen.
      Serial.println("NO SCREEN!");                               // Screen init failed. Tell user.
      Serial.flush();                                             // Make sure the message gets out.
      while(true);                                                // Lock the process here.
   }
   if (!SD.begin(ADA_1947_SHIELD_SDCS)) {                         // With icons, we now MUST have an SD card.
      Serial.println("NO SD CARD!");                              // Tell user we have no SD card.
      Serial.flush();                                             // Make sure the message gets out.
      while(true);                                                // Lock the process here.
   }
   ourEventMgr.begin();                                           // Startup our event manager.
   ourOS.begin();                                                 // Boot OS manager.
   nextPanel = breakoutApp;                                       // <<-- URISH LOOK HERE!!
}


void loop() {     // During loop..
   
  idle();         // Idlers get their time.
  ourOS.loop();   // ourOS gets time to pass on to the current panel.
}