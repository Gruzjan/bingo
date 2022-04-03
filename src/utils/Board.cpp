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

void Board::draw(bool preview){
    window->Draw(UIElement);
    for(unsigned long i = 0; i < tiles.size(); i++){
        if(!preview)
            tiles.at(i).draw();
        else
            previewTiles.at(i).draw();
    }
}

int Board::getSize(){
    return size;
}

void Board::setSize(int size){
    this->size = size;
    tiles.clear();
    previewTiles.clear();
    // Set board scale depending on size
    int tX = getX(), tY = getY();
    int tileSize = 160;
    if(size == 5)
        tileSize = 125;

    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++){
            previewTiles.emplace_back(Tile(tX + j * 5 + j * tileSize, tY + i * 5 + i * tileSize, tileSize, tileSize, *window));
            tiles.emplace_back(Tile(tX + j * 5 + j * tileSize + 50, tY + i * 5 + i * tileSize + 50, tileSize + 50, tileSize + 50, *window));
        }
}

void Board::setPasswords(std::vector<std::wstring> passwords){
    srand(time(NULL));
    unsigned int boardMin = freeTile ? size * size - 1 : size * size;
    int limit = passwords.size() <= boardMin ? passwords.size() : boardMin; 

    for(int i = 0; i < limit; i++){
        int index = rand() % passwords.size();
        previewTiles.at(i).setPassword(passwords.at(index));
        passwords.erase(passwords.begin() + index);
    }
}

void Board::setFreeTile(bool free){
    freeTile = free;
    if(free && getSize() == 5){
        previewTiles.at(12).setCheck(true);
        previewTiles.at(12).UIElement.SetColor(smk::Color::Green); // Free color
    }
    else if(!free){
        previewTiles.at(12).setCheck(false);
        previewTiles.at(12).UIElement.SetColor(smk::Color::White); // Default color
    }
}

bool Board::getFreeTile(){
    return freeTile;
}

smk::Transformable &Board::getBoard() {
    return UIElement;
}

void Board::setTilesOnClickAction(){
    for(auto x : previewTiles){
        x.onClick([&]{x.setCheck(true); UIElement.SetColor(smk::Color::Grey);});
    }
}
