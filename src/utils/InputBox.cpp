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

void InputBox::onClick(){
    if (window->input().IsMousePressed(GLFW_MOUSE_BUTTON_1)) {
        glm::vec2 cursor = window->input().cursor();

        if ((cursor.x >= this->x && cursor.x <= this->x + this->width)
        && (cursor.y >= this->y && cursor.y <= this->y + this->height)){
            focused = true;
            UIElement.SetColor(smk::Color::Green);
        }
        else{
            focused = false;
            UIElement.SetColor(smk::Color::Red);
        }
    }
}

void InputBox::write(wchar_t character) {
    if(focused){
        if(input.empty())
            input = character;
        else
            input += character;
    
        text = smk::Text(font, L"Input = " + input);
        window->Draw(text);
        UIElement.SetColor(smk::Color::Yellow);
    }

    // auto listener = window->input().MakeCharacterListener();
    // wchar_t character = 'a';
    // while(listener->Receive(&character) && focused) {
    //     UIElement.SetColor(smk::Color::Yellow);
    //     if(input.empty())
    //         input = character;
    //     else
    //         input += character;
    // }
    // if(window->input().IsKeyReleased(GLFW_KEY_BACKSPACE) && !input.empty() && focused)
    //     input.erase(input.size() - 1);

}

void InputBox::draw() {
    window->Draw(UIElement);
}

smk::Transformable &InputBox::getInputBox(){
    return UIElement;
}

smk::Text &InputBox::getText(){
    return text;
}