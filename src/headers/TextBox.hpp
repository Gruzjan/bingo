#pragma once
#include <iostream>

#include "smk/Window.hpp"
#include "smk/Input.hpp"

#include "headers/UIElement.hpp"

class TextBox : public UIElement {
private:
    int x, y, height, width;
    std::string text = "";
    bool focused = false;
    smk::Window& window;
public:
    TextBox(int, int, int, int, smk::Window&);
    void setX(int);
    void setY(int);
    int getX();
    int getY();
    bool click();
    bool hover();
    void onClick(std::function<void()>);
    void onHover(std::function<void()>);
    void onFocus(std::function<void()>);
    void draw();
    void write();
};