#include "MyDisplay.hpp"

MyDisplay::MyDisplay() {}

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
    if (ID == 0xD3D3)
        ID = 0x9486; // write-only shield
    _tft.begin(ID);
    _tft.setRotation(0); // PORTRAIT
    _tft.fillScreen(BLACK);
    _ts = TouchScreen(XP, YP, XM, YM, 300);
    refresh = 1;
}

void MyDisplay::drawTemplate()
{
    on_btn.initButton(&_tft, 60, 200, 100, 40, WHITE, CYAN, BLACK, "ON", 2);
    off_btn.initButton(&_tft, 180, 200, 100, 40, WHITE, CYAN, BLACK, "OFF", 2);
    on_btn.drawButton(false);
    off_btn.drawButton(false);
    _tft.fillRect(40, 80, 160, 80, RED);
}

void MyDisplay::drawPanel(Panel *panel1)
{
    Panel &panel = *panel1; // Dereference the pointer to get the actual panel object
    for (Task &task : panel.task)
    {
        switch (task.type)
        {
        case TaskType::Text:
            _tft.setTextColor(task.value.text->color, task.value.text->bgColor);
            _tft.setCursor(task.value.text->x, task.value.text->y);
            _tft.setTextSize(task.value.text->fontSize);
            _tft.print(*(task.value.text->text));
            Serial.println("Text drawn");
            break;
        case TaskType::Color:
            _tft.fillScreen(task.value.color);
            Serial.println("Color drawn");
            break;
        // case TaskType::Panel:
        //     drawPanel(*(task.value.panel)); // Recursive call to draw nested panels
        // break;
        case TaskType::Imagee:
            Serial.println("Inside image case");
            if (task.value.image != nullptr)
            {
                Serial.println("Image pointer is not null");
                ImageData &img = *(task.value.image);
                Serial.print("Image position: x=");
                Serial.print(img.x);
                Serial.print(", y=");
                Serial.print(img.y);
                Serial.print(", width=");
                Serial.print(img.width);
                Serial.print(", height=");
                Serial.println(img.height);
                Serial.print("Image data pointer: 0x");
                Serial.println((unsigned int)img.data, HEX);

                drawImageFromProgmem(img.x, img.y, img.width, img.height, img.data);
                Serial.println("Image drawn using helper method");
            }
            else
            {
                Serial.println("Error: Image object is null!");
            }
            break;
        case TaskType::Button:
            Button &btn = *(task.value.buttonData); // Dereference the pointer to create a reference
            btn.initButton(&_tft, btn._x, btn._y, btn._width, btn._height, btn._outlinecolor, btn._colorOn, btn._textColor, btn._label->c_str(), 2);
            btn.drawButton(false);
            Serial.println("Button drawn");
            break;
        default:
            break;
        }
    }
}

void MyDisplay::drawImageFromProgmem(int x, int y, int width, int height, const uint16_t *progmemData)
{
    _tft.setAddrWindow(x, y, x + width - 1, y + height - 1);
    _tft.pushColors((const uint8_t *)progmemData, width * height, 1, false);
    _tft.setAddrWindow(0, 0, _tft.width() - 1, _tft.height() - 1);
}

bool MyDisplay::Touch_getXY(void)
{
    MCUFRIEND_kbv &tft = _tft; // Reference to the display object
    TouchScreen ts = _ts;      // Reference to the touchscreen object

    TSPoint p = ts.getPoint();
    pinMode(YP, OUTPUT); // restore shared pins
    pinMode(XM, OUTPUT);
    digitalWrite(YP, HIGH); // because TFT control pins
    digitalWrite(XM, HIGH);
    bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
    if (pressed)
    {
        pixel_x = map(p.x, TS_LEFT, TS_RT, 0, tft.width()); //.kbv makes sense to me
        pixel_y = map(p.y, TS_TOP, TS_BOT, 0, tft.height());
    }
    return pressed;
}
