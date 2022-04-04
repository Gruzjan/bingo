#pragma once
#include <functional>
#include <vector>
#include <stdlib.h>
#include <time.h> 

#include <smk/Color.hpp>
#include <smk/Shape.hpp>
#include <smk/Window.hpp>

#include "headers/Tile.hpp"
#include "headers/UIElement.hpp"

class Board : virtual public UIElement{
private:
    int size;
    std::vector<Tile*> tiles;
    std::vector<Tile*> previewTiles;
    bool freeTile = false;
    std::vector<std::wstring> winningWords;
public:
    Board(int, int, int, int, smk::Window&);
    void draw(bool);
    bool isBingo();
    int getSize();
    void setSize(int);
    void setPasswords(std::vector<std::wstring>);
    void setFreeTile(bool);
    bool getFreeTile();
    std::vector<Tile*> getTiles();
    smk::Transformable &getBoard();
    void setTilesOnClickAction();
    std::vector<std::wstring> getWinningWords();
    void uncheckAll();
};