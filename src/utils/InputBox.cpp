#include "headers/InputBox.hpp"
#include "smk/Text.hpp"


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

    listener = window.input().MakeCharacterListener();
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

void InputBox::writeListener(std::function<void(void)> f) {
    // Just focused
    if (focused) {
        // In case you would like to intercept a key
        f();

        // Would love to use switch here but listener doesn't 
        // listen for modifier keys e.g. `enter`, `alt` etc.

        // Backspace handler
        if (
            (window->input().IsKeyPressed(GLFW_KEY_BACKSPACE))
            && input.size() > 0
        ) {
            input = input.substr(0, input.size() - 1);
            this->setText(input);
            std::cerr << "deleter" << std::endl;
        }

        // Enter handler
        else if 
        (
            (window->input().IsKeyPressed(GLFW_KEY_ENTER))
            && input.size() > 0
        ) {
            input = L"";
            this->setText(input);
            std::cerr << "enterer" << std::endl;
        }

        // Default
        UIElement.SetColor(smk::Color::Yellow);
    }

    // Focused and key pressed
    // Cant be inside above `if` statement because
    // it will register all keys pressed before being focused
    while(listener->Receive(&character) && focused) {
        this->appendText(character);
        std::cerr << "keyer" << std::endl;
    }
}

void InputBox::draw() {
    window->Draw(UIElement);
    window->Draw(text);
}

smk::Transformable &InputBox::getInputBox(){
    return UIElement;
}

std::wstring InputBox::getText(){
    return input;
}

void InputBox::appendText(wchar_t text) {
    input += text;
    if (input.size() > 12)
        this->text.SetString(L"Input: " + input.substr(input.size() - 12, input.size()));
    else
        this->text.SetString(L"Input: " + input);
}

void InputBox::setText(std::wstring text) {
    input = text;
    if (input.size() > 12)
        this->text.SetString(L"Input: " + input.substr(input.size() - 12, input.size()));
    else
        this->text.SetString(L"Input: " + input);
}