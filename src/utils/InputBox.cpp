#include "headers/InputBox.hpp"


InputBox::InputBox(int x, int y, int width, int height, smk::Window &window){
    this->x = x;
    this->y = y;

    // Calculate hitboxes based on that
    this->width = width;
    this->height = height;

    // Listen for events and maybe add
    // custom render function
    this->window = &window;
    this->UIElement = smk::Shape::Square();

    // Set properties
    UIElement.SetScaleX(width);
    UIElement.SetScaleY(height);
    UIElement.SetPosition(x, y);
    UIElement.SetColor(smk::Color::Cyan); 
}
 //: x(x), y(y), height(height), width(width), window(window) {};

void InputBox::write() {
    auto listener = window->input().MakeCharacterListener();
    wchar_t character;
    while(listener->Receive(&character) && focused) {
        if(text.empty())
            text = character;
        else
            text += character;
    }

    if(window->input().IsKeyReleased(GLFW_KEY_BACKSPACE) && !text.empty() && focused)
        text.erase(text.size() - 1);
}

smk::Transformable &InputBox::getInputBox(){
    return UIElement;
}