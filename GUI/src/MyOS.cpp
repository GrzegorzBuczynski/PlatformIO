#include "MyOS.hpp"
#include "Panel.hpp"


#define BEEP_PIN     14                      // The digital pin choosen for the beeper.
#define SCREEN_PIN   25                      // The ananlog pin choosen for the screen backlight.
char systemFolder[]  = "/system/";           // Where we decided to store the systemp folder on our SD card.
char panelFolder[]   = "/system/appFiles/";  // Where we decided to store the app folders on our SD card.


// **************************************
// ************** MyOS **************
// **************************************



MyOS::MyOS(void) {
    display.begin(); // Initialize the display
    // display.setRotation(0); // Set rotation to 0 by default
    // panel = new HomePanel(432, 240); // Initialize the home panel
    // display.drawPanel(*panel); // Draw the home panel on the display
 }


MyOS::~MyOS(void) { 
    delete panel; // Clean up the panel object
 }


// // The hardware is online, do hookups.
// int MyOS::begin(void) {
   
//    pinMode(BEEP_PIN, OUTPUT);       // Setup The beeper pin.
//    digitalWrite(BEEP_PIN, HIGH);    // Means off.
//    return 0;           // Return result of the inherited
// }

// //void backlightOn(void) { ourOSPtr->setBrightness(255); }

// // We need to write our own panel creation method.
// panel* MyOS::createPanel(int panelID) {
   
//    panel* result;
   
//    beep();
//    //setBrightness(0);
//    switch (panelID) {
//       case homeApp      : result = new homeScr();                    break;
//       case calcApp      : result = new rpnCalc(this,panelID);        break;
//       case iconEditApp : result = new iconEdit(this,panelID);       break;
//       case breakoutApp  : result = new breakout(this,panelID);       break;
//       //case starTrekApp  : result = new starTrekPanel(this,panelID);  break;
//       //case testApp      : result = new testAppPanel(this,panelID);  break;
//       default           : result = NULL;
//    }
//    return(result);
// }


// // Only WE know how to make it beep.
// void MyOS::beep(void) { tone(BEEP_PIN, 750,20); }


// // Here's the pin if you want to use it yourself.
// int MyOS::getTonePin(void) {return BEEP_PIN; }


// // And how to control the screen brightness.
// void MyOS::setBrightness(byte brightness) { analogWrite(SCREEN_PIN,brightness); }


// char*  MyOS::getSystemFolder(void) { return systemFolder; }


// // Hand this an appID and get back a pointer to the path of its data folder.
// char* MyOS::getPanelFolder(int panelID) {
     
//    strcpy(pathBuff,panelFolder);
//    switch (panelID) {
//       case homeApp      : return NULL;
//       case calcApp      : 
//          strcat(pathBuff,"rpnCalc/");
//          return pathBuff;
//       break;
//       case iconEditApp  :
//          strcat(pathBuff,"iconEdit/");
//          return pathBuff;
//       break;
//       case breakoutApp  :
//          strcat(pathBuff,"breakout/");
//          return pathBuff;
//       break; 
// //      case starTrekApp  :
// //         strcat(pathBuff,"starTrek/");
// //         return pathBuff;
// //      break;
// //      case testApp      :
// //         strcpy(pathBuff,getSystemFolder());
// //         strcat(pathBuff,"icons/standard/");
// //         return pathBuff;
// //      break;
//       default           : return NULL;
//    }
// }