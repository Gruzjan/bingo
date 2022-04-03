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
    std::wstring password;
    bool checked = false;
public:
    Tile(int, int, int, int, smk::Window&);
    void draw();
    std::wstring getPassword();
    void setPassword(std::wstring);
    void setCheck(bool);
    void switchCheck();
    bool isChecked();
    smk::Transformable &getTile();
};