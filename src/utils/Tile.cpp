#include "headers/Tile.hpp"

Tile::Tile(int x, int y, int width, int height, smk::Window &window) {
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
    UIElement.SetColor(smk::Color::White);
}

void Tile::draw(){
    window->Draw(UIElement);
}

void Tile::setPassword(std::wstring password){
    this->password = password;
}

std::wstring Tile::getPassword(){
    return password;
}

void Tile::setCheck(bool check){
    std::cerr << "setting check to: " << check << std::endl; 
    checked = check;
    
    if(checked){
        UIElement.SetColor(smk::Color::Yellow);
        std::cerr << "tile is checked, color should be yellow (set)" << std::endl; 
    }
}

void Tile::switchCheck(){
    checked = !checked;
    std::cerr << "set check to: " << checked << std::endl; 
    UIElement.SetColor(smk::Color::White);
    if(checked){
        UIElement.SetColor(smk::Color::Yellow);
        std::cerr << "tile is checked, color should be yellow (switch)" << std::endl; 
    }
}

void Tile::setText(smk::Text *text){
    this->text = text;
}

smk::Text &Tile::getText(){
    return *text;
}

bool Tile::isChecked(){
    return checked;
}

smk::Transformable &Tile::getTile() {
    return UIElement;
}
