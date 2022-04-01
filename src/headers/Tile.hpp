#pragma once
#include <functional>

#include <smk/Color.hpp>
#include <smk/Shape.hpp>
#include <smk/Window.hpp>
#include <smk/Text.hpp>
#include <smk/Font.hpp>

#include "headers/UIElement.hpp"

class Tile : virtual public UIElement{
private:
    smk::Text *text;
    std::string password;
    bool checked = false;
public:
    Tile(int, int, int, int, smk::Window&);
    void draw();
    void setText(smk::Font&, std::string);
    std::string getPassword();
    void switchCheck();
    smk::Text &getText();
    smk::Transformable &getTile();
};