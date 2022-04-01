#include "headers/Board.hpp"

Board::Board(int x, int y, int width, int height, smk::Window &window) {
    this->x = x;
    this->y = y;

    // Calculate hitboxes based on that
    this->width = width;
    this->height = height;

    // Listen for events and maybe add
    // custom render function
    this->window = &window;
    this->UIElement = smk::Shape::Square();

    // Set properties
    UIElement.SetScaleX(width);
    UIElement.SetScaleY(height);
    UIElement.SetPosition(x, y);
    UIElement.SetColor(smk::Color::Blue);
}

void Board::draw(){
    window->Draw(UIElement);
    for(unsigned long i = 0; i < tiles.size(); i++)
       tiles.at(i).draw();
}

int Board::getSize(){
    return size;
}

void Board::setSize(int size){
    this->size = size;
    tiles.clear();
    //set board scale depending on size
    int tX = getX(), tY = getY();
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            tiles.emplace_back(Tile(tX + j * 5 + j * 125, tY + i * 5 + i * 125, 125, 125, *window));
    
    
    
    // int tX = getX(), tY = getY();
    // for(int i = 0; i < size; i++)
    //     for(int j = 0; j < size; j++)
    //         tiles.emplace_back(Tile(tX + 2 + j * 75, tY + 2 + i * 75, 75, 75, *window));
}

void Board::setFreeTile(bool free){
  freeTile = free;
}

smk::Transformable &Board::getBoard() {
    return UIElement;
}
