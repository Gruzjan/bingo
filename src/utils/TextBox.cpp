#include "headers/TextBox.hpp"


TextBox::TextBox(int x, int y, int height, int width, smk::Window &window) : x(x), y(y), height(height), width(width), window(window) {};

void TextBox::setX(int x) {
    this->x = x;
}

void TextBox::setY(int y) {
    this->y = y;
}

int TextBox::getX() {
    return this->x;
}

int TextBox::getY() {
    return this->y;
}

bool TextBox::click() {}

bool TextBox::hover() {};
void TextBox::onClick(std::function<void()>) {};
void TextBox::onHover(std::function<void()>) {};
void TextBox::onFocus(std::function<void()>) {};
void TextBox::draw() {};
void TextBox::write() {
    auto listener = window.input().MakeCharacterListener();
    wchar_t character;
    while(listener->Receive(&character)) {
        text += character;
    } 
}