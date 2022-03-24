#include <smk/Color.hpp>
#include <smk/Shape.hpp>
#include <smk/Window.hpp>
#include <smk/Input.hpp>

#include "headers/Button.hpp"

Button::Button(int x, int y, int width, int height, smk::Window &window) {
    this->x = x;
    this->y = y;

    // Calculate hitboxes based on that
    this->width = width;
    this->height = height;

    // Listen for events and maybe add
    // custom render function
    this->window = &window;
    this->button = smk::Shape::Square();

    // Set properties
    button.SetScaleX(width);
    button.SetScaleY(height);
    button.SetPosition(x, y);
    button.SetColor(smk::Color::Blue);
}

int Button::getX() {
    return this->x;
}

int Button::getY() {
    return this->y;
}

void Button::setX(int x) {
    this->x = x;
    button.SetPosition(x, y);
}

void Button::setY(int y) {
    this->y = y;
    button.SetPosition(x, y);
}

smk::Transformable &Button::getButton() {
    return button;
}

bool Button::click() {
    if (window->input().IsMousePressed(GLFW_MOUSE_BUTTON_1)) {
        return Button::hover();
    }
    return false;
}

bool Button::hover() {
    glm::vec2 cursor = window->input().cursor(); // helper

    if ((cursor.x >= this->x && cursor.x <= this->x + this->width)
    && (cursor.y >= this->y && cursor.y <= this->y + this->height)) {
        return true;
    }
    return false;
}

void Button::onClick(const std::function<void()> f) {
    if (window->input().IsMousePressed(GLFW_MOUSE_BUTTON_1)) {
        // onHover already implements whether the mouse is
        // inside the box so I can just call it
        Button::onHover(f);
    }
}

void Button::onHover(const std::function<void()> f) {
    glm::vec2 cursor = window->input().cursor();

    if ((cursor.x >= this->x && cursor.x <= this->x + this->width)
    && (cursor.y >= this->y && cursor.y <= this->y + this->height)) {
        f();
    }
}

void Button::draw() {
    window->Draw(button);
}