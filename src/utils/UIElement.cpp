#include "headers/UIElement.hpp"

int UIElement::getX() {
    return this->x;
}

int UIElement::getY() {
    return this->y;
}

void UIElement::setX(int x) {
    this->x = x;
    UIElement.SetPosition(x, y);
}

void UIElement::setY(int y) {
    this->y = y;
    UIElement.SetPosition(x, y);
}

void UIElement::onClick(const std::function<void()> f) {
    if (window->input().IsMousePressed(GLFW_MOUSE_BUTTON_1)) {
        // onHover already implements whether the mouse is
        // inside the box so I can just call it
        UIElement::onHover(f);
    }
}

void UIElement::onHover(const std::function<void()> f) {
    glm::vec2 cursor = window->input().cursor();

    if ((cursor.x >= this->x && cursor.x <= this->x + this->width)
    && (cursor.y >= this->y && cursor.y <= this->y + this->height)) {
        f();
    }
}

void UIElement::draw() {
    window->Draw(UIElement);
}