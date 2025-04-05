#include "MyDisplay.hpp"

MyDisplay::MyDisplay(){}

MyDisplay::~MyDisplay()
{
    // Cleanup if needed
}

void MyDisplay::begin()
{
    uint16_t ID = _tft.readID();
    Serial.print("TFT ID = 0x");
    Serial.println(ID, HEX);
    Serial.println("Calibrate for your Touch Panel");
    if (ID == 0xD3D3) ID = 0x9486; // write-only shield
    _tft.begin(ID);
    _tft.setRotation(0);            //PORTRAIT
    _tft.fillScreen(BLACK);
    _ts = TouchScreen(XP, YP, XM, YM, 300);
    refresh = 1;
}


void MyDisplay::drawTemplate()
{
    on_btn.initButton(&_tft,  60, 200, 100, 40, WHITE, CYAN, BLACK, "ON", 2);
    off_btn.initButton(&_tft, 180, 200, 100, 40, WHITE, CYAN, BLACK, "OFF", 2);
    on_btn.drawButton(false);
    off_btn.drawButton(false);
    _tft.fillRect(40, 80, 160, 80, RED);

}

void MyDisplay::drawPanel(Panel *panel1)
{
    Panel &panel = *panel1; // Dereference the pointer to get the actual panel object
    for ( Task &task : panel.task) {
        switch (task.type) {
            case TaskType::Text:
                _tft.setTextColor(task.value.text->color, task.value.text->bgColor);
                _tft.setCursor(task.value.text->x, task.value.text->y);
                _tft.setTextSize(task.value.text->fontSize);
                _tft.print(*(task.value.text->text));
                break;
            case TaskType::Color:
                _tft.fillScreen(task.value.color);
                break;
            case TaskType::Image:
                // Implement image drawing logic here
                break;
            // case TaskType::Panel:
            //     drawPanel(*(task.value.panel)); // Recursive call to draw nested panels
                // break;
            case TaskType::Button:
                // task.value.button->drawButton();
                break;
            default:
                break;
        }
    }

}

bool MyDisplay::Touch_getXY(void)
{
    MCUFRIEND_kbv &tft = _tft; // Reference to the display object
    TouchScreen ts = _ts; // Reference to the touchscreen object

    TSPoint p = ts.getPoint();
    pinMode(YP, OUTPUT);      //restore shared pins
    pinMode(XM, OUTPUT);
    digitalWrite(YP, HIGH);   //because TFT control pins
    digitalWrite(XM, HIGH);
    bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
    if (pressed) {
        pixel_x = map(p.x, TS_LEFT, TS_RT, 0, tft.width()); //.kbv makes sense to me
        pixel_y = map(p.y, TS_TOP, TS_BOT, 0, tft.height());
    }
    return pressed;
}
