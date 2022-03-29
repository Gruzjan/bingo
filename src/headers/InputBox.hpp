#pragma once
#include <iostream>
#include <functional>

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
    smk::Text text = smk::Text(font, L"Input: ");
public:
    InputBox(int, int, int, int, smk::Window&);
    void onClick();
    void write(wchar_t);
    void draw();
    smk::Transformable &getInputBox();
    smk::Text &getText();
};