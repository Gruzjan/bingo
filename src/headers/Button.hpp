#pragma once
#include <functional>

#include <smk/Color.hpp>
#include <smk/Shape.hpp>
#include <smk/Window.hpp>

#include "headers/UIElement.hpp"

class Button : virtual public UIElement{
public:
    Button(int, int, int, int, smk::Window&);
    smk::Transformable &getButton();
};