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
    UIElement.SetColor(smk::Color::Cyan);
}

void Board::draw(bool preview){
    window->Draw(UIElement);
    for(unsigned long i = 0; i < tiles.size(); i++){
        if(!preview)
            tiles.at(i)->draw();
        else
            previewTiles.at(i)->draw();
    }
}

bool Board::isBingo(){
    int selected = 0;
    // Check for rows
    for (int i = 0; i < (int)tiles.size(); i++) {
        if (i % size == 0) {
            selected = 0;
            winningWords.clear();
        }
        if (tiles[i]->isChecked()) {
            selected++;
            winningWords.push_back(tiles[i]->getPassword());
        }
        if (selected == size) return true;
    }

    // Check for columns
    selected = 0;
    int a = 0;
    int b = -1;
    for(int i = 0; i < (int)tiles.size(); i++) {
        if (a % size == 0) {
            a = 0;
            b++;
            selected = 0;
            winningWords.clear();
        }
        if (tiles[(a * size) + b]->isChecked()) {
            selected++;
            winningWords.push_back(tiles[(a * size) + b]->getPassword());
        }
        if (selected == size) return true;
        a++;
    }

    return false;
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
            previewTiles.emplace_back(new Tile(tX + j * 5 + j * tileSize, tY + i * 5 + i * tileSize, tileSize, tileSize, *window));
            tiles.emplace_back(new Tile(tX + j * 5 + j * (tileSize + 50), tY + i * 5 + i * (tileSize + 50), (tileSize + 50), (tileSize + 50), *window));
        }
}

void Board::setPasswords(std::vector<std::wstring> passwords){
    srand(time(NULL));
    unsigned int boardMin = freeTile ? size * size - 1 : size * size;
    int limit = passwords.size() <= boardMin ? passwords.size() : boardMin; 

    for(int i = 0; i < limit; i++){
        int index = rand() % passwords.size();
        tiles.at(i)->setPassword(passwords.at(index));
        previewTiles.at(i)->setPassword(passwords.at(index));
        passwords.erase(passwords.begin() + index);
    }

    if(freeTile && size == 5){
        tiles.at(24)->setPassword(tiles.at(12)->getPassword());
        tiles.at(12)->setPassword(L"Free!");

    }
}

void Board::setFreeTile(bool free){
    freeTile = free;
    previewTiles.at(12)->setCheck(free);
    if(free && getSize() == 5)
        previewTiles.at(12)->UIElement.SetColor(smk::Color::Green); // Free color
    else if(!free)
        previewTiles.at(12)->UIElement.SetColor(smk::Color::White); // Default color
}

bool Board::getFreeTile(){
    return freeTile;
}

std::vector<Tile*> Board::getTiles(){
    return tiles;
}

smk::Transformable &Board::getBoard() {
    return UIElement;
}

void Board::setTilesOnClickAction(){
    for(auto x : tiles)
        x->onClick([&]{x->switchCheck(); std::cerr << "tile on click" << std::endl;});
    
}

std::vector<std::wstring> Board::getWinningWords() {
    return this->winningWords;
}

void Board::uncheckAll() {
    for (auto x : tiles) {
        if (x->isChecked()) {
            x->switchCheck();
        }
    }
}