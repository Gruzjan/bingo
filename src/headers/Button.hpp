#pragma once
#include <functional>

#include <smk/Color.hpp>
#include <smk/Shape.hpp>
#include <smk/Window.hpp>
#include <smk/Input.hpp>

#include "headers/UIElement.hpp"

class Button : public UIElement {
private:
    int x, y, height, width;
    smk::Window *window;
    smk::Transformable button;
public:
    Button(int, int, int, int, smk::Window&);
    void setX(int);
    void setY(int);
    int getX();
    int getY();
    smk::Transformable &getButton();
    bool click();
    bool hover();
    void onClick(std::function<void()>);
    void onHover(std::function<void()>);
    void draw();
};