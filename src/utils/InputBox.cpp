#include "headers/InputBox.hpp"
#include <smk/Text.hpp>
#include <locale>
#include <codecvt>

InputBox::InputBox(int x, int y, int width, int height, smk::Window &window, int fontSize) {
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
    UIElement.SetColor(smk::Color::Blue); 

    inputText = smk::Text(font, input);
    inputText.SetColor(smk::Color::White);
    inputText.SetPosition(x, y);

    font = smk::Font("/resources/SHPinscher-Regular.otf", fontSize);

    listener = window.input().MakeCharacterListener();
}

void InputBox::onClick(){
    if (window->input().IsMousePressed(GLFW_MOUSE_BUTTON_1)) {
        glm::vec2 cursor = window->input().cursor();

        if ((cursor.x >= this->x && cursor.x <= this->x + this->width)
        && (cursor.y >= this->y && cursor.y <= this->y + this->height)){
            UIElement.SetColor(smk::Color::Grey);
            focused = true;
        }
        else{
            focused = false;
            UIElement.SetColor(smk::Color::RGBA(0.6, 0.4, 0.6, 0.5));
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
            this->setInputText(input);
        }else if (
            (window->input().IsKeyPressed(GLFW_KEY_BACKSPACE))
            && input.size() == 0 && passwords.size() > 0
        ) 
            passwords.pop_back();
        

        // Enter handler
        else if 
        (
            (window->input().IsKeyPressed(GLFW_KEY_ENTER))
            && input.size() > 0
        ) {
            input = L"";
            this->setInputText(input);
        }
        // Default here \/
    
    }

    // Focused and key pressed
    // Cant be inside above `if` statement because
    // it will register all keys pressed before being focused
    while(listener->Receive(&character) && focused)
        this->appendInputText(character);

}

void InputBox::draw() {
    std::wstring passwordsTemp;
    unsigned long i = 0;
    if(passwords.size() >= 16)
        i = passwords.size() - 16;

    for(; i < passwords.size(); i++){
        if(passwords.at(i).size() > 18)
            passwordsTemp += L".." + passwords.at(i).substr(passwords.at(i).size() - 18, passwords.at(i).size()) + wchar_t('\n');
        else
            passwordsTemp += passwords.at(i) + wchar_t('\n');
    }
    smk::Text passwordsText = smk::Text(font, passwordsTemp);
    
    if(passwords.size() > 16)
        i = 16;
    inputText.SetPosition(getX(), getY() + i * font.line_height ());
    passwordsText.SetPosition(getX(), getY());

    window->Draw(UIElement);
    window->Draw(passwordsText);
    if (input.size() > 0) {
        window->Draw(inputText);
    }
}

smk::Transformable &InputBox::getInputBox(){
    return UIElement;
}

std::wstring InputBox::getInputText() {
    return input;
}

std::string InputBox::getInputString() {
    return std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(input);
}

void InputBox::appendInputText(wchar_t text) {
    input += text;
    if (input.size() > 18)
        this->inputText.SetString(input.substr(input.size() - 18, input.size()));
    else
        this->inputText.SetString(input);
}

void InputBox::setInputText(std::wstring text) {
    input = text;
    if (input.size() > 18)
        this->inputText.SetString(input.substr(input.size() - 18, input.size()));
    else
        this->inputText.SetString(input);
}

void InputBox::pushBackPassword(std::wstring password){
    passwords.push_back(password);
}

void InputBox::drawRaw() {
    window->Draw(UIElement);
    if (input.size() > 0) {
        window->Draw(inputText);
    }
}

smk::Text InputBox::getText() {
    return inputText;
}

void InputBox::drawText() {
    window->Draw(inputText);
}

void InputBox::setPasswords(std::vector<std::wstring> passwords){
    this->passwords = passwords;
}

std::vector<std::wstring> InputBox::getPasswords(){
    return passwords;
}

void InputBox::clearPasswords(){
    passwords.clear();
}