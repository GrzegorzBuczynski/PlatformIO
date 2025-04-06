#include "Task.hpp"

Task::Task() : type(TaskType::None) {
    value.text = nullptr;
}

Task::~Task() {
    clear(); // Clean up resources if needed
}

void Task::setText(TextSprite* ptr) {
    clear();
    value.text = ptr;
    type = TaskType::Text;
}

void Task::setColor(uint16_t c) {
    clear();
    value.color = c;
    type = TaskType::Color;
}

void Task::setImage(ImageData* img) {
    clear();
    value.image = img;
    type = TaskType::Imagee;
}

void Task::setImage() {
    clear();
    value.image = nullptr; // Set to nullptr or handle as needed
    type = TaskType::Imagee;
}

void Task::setButton(Button* b) {
    clear();
    value.button = b;
    type = TaskType::Button;
}
void Task::setPanel(Panel* p) {
    clear();
    value.panel = p;
    type = TaskType::Panel;
}


void Task::clear() {
    value.text = nullptr; // reset dowolnego wskaźnika
    type = TaskType::None;
}
