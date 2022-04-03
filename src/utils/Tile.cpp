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
    if(checked)
        UIElement.SetColor(smk::Color::Green);
    window->Draw(UIElement);
}

void Tile::setPassword(std::wstring password){
    this->password = password;
}

std::wstring Tile::getPassword(){
    return password;
}

void Tile::setCheck(bool check){ //TODO: WTF
    std::cerr << "setCheck " << check << std::endl; 
    checked = check;
    
    if(checked){
        UIElement.SetColor(smk::Color::Yellow);
        std::cerr << "siema kurwy" << std::endl; 
    }
}

void Tile::switchCheck(){
    checked = !checked;
}

bool Tile::isChecked(){
    return checked;
}

smk::Transformable &Tile::getTile() {
    return UIElement;
}
