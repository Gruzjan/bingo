#pragma once
#include <iostream>
#include <functional>
#include <vector>

#include "smk/Window.hpp"
#include "smk/Color.hpp"
#include "smk/Shape.hpp"
#include "smk/Input.hpp"

#include "headers/UIElement.hpp"

class InputBox : virtual public UIElement{
private:
    std::wstring input;
    bool focused = false;
    smk::Font font = smk::Font("/resources/SHPinscher-Regular.otf", 48);
    smk::Text inputText = smk::Text(font, L"");
    smk::Input::CharacterListener listener;
    wchar_t character;
    std::vector<std::wstring> passwords;
public:
    InputBox(int, int, int, int, smk::Window&);
    void onClick();
    void writeListener(std::function<void()>);
    void draw();
    smk::Transformable &getInputBox();
    std::wstring getInputText();
    void setInputText(std::wstring);
    void appendInputText(wchar_t);
    void pushBackPassword(std::wstring);
    void setPasswords(std::vector<std::wstring>);
    std::vector<std::wstring> getPasswords();
    void clearPasswords();
};
