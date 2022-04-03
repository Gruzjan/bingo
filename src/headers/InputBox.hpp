#pragma once
#include <iostream>
#include <functional>
#include <vector>

#include <smk/Window.hpp>
#include <smk/Color.hpp>
#include <smk/Shape.hpp>
#include <smk/Input.hpp>
#include <smk/Font.hpp>

#include "headers/UIElement.hpp"

class InputBox : virtual public UIElement{
private:
    std::wstring input = L"";
    bool focused = false;
    smk::Font font;
    smk::Text inputText;
    smk::Input::CharacterListener listener;
    wchar_t character;
    std::vector<std::wstring> passwords;
public:
    InputBox(int, int, int, int, smk::Window&, int);
    void onClick();
    void writeListener(std::function<void()>);
    void draw();
    smk::Transformable &getInputBox();
    std::wstring getInputText();
    std::string getInputString();
    void setInputText(std::wstring);
    void appendInputText(wchar_t);
    void pushBackPassword(std::wstring);
    void drawRaw();
    void drawText();
    smk::Text getText();
};
