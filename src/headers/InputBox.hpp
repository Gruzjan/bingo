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
    std::wstring text;
    bool focused = false;
public:
    InputBox(int, int, int, int, smk::Window&);
    void write();
    smk::Transformable &getInputBox();
};