#pragma once
#include <functional>

#include "smk/Transformable.hpp"

class UIElement {
public:
    virtual void setX(int) = 0;
    virtual void setY(int) = 0;
    virtual int getX() = 0;
    virtual int getY() = 0;
    virtual bool click() = 0;
    virtual bool hover() = 0;
    virtual void onClick(std::function<void()>) = 0;
    virtual void onHover(std::function<void()>) = 0;
    virtual void draw() = 0;
};