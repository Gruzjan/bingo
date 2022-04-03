#pragma once
#include <functional>

#include <smk/Window.hpp>
#include <smk/Input.hpp>
#include <smk/Color.hpp>
#include "smk/Transformable.hpp"

class UIElement {
public:
    int x, y, width, height;
    smk::Transformable UIElement;
    smk::Window *window;

    void setX(int);
    void setY(int);
    int getX();
    int getY();
    void onClick(std::function<void()>);
    void onHover(std::function<void()>);
    void setColor(glm::vec4);
    void draw();
};