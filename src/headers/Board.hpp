#pragma once
#include <functional>
#include <vector>

#include <smk/Color.hpp>
#include <smk/Shape.hpp>
#include <smk/Window.hpp>

#include "headers/Tile.hpp"
#include "headers/UIElement.hpp"

class Board : virtual public UIElement{
private:
    int size;
    std::vector<Tile> tiles;// = new std::vector<Tile>();
    bool freeTile = false;
public:
    Board(int, int, int, int, smk::Window&);
    void draw();
    int getSize();
    void setSize(int);
    void setFreeTile(bool);
    smk::Transformable &getBoard();
};