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
    //window->Draw(text);
}

void Tile::setText(smk::Font &font, std::string password){
    this->password = password;
    text = new smk::Text(font, password);
    text->SetPosition(getX(), getY());
    text->SetColor(smk::Color::Magenta);
}

std::string Tile::getPassword(){
    return password;
}

void Tile::switchCheck(){
    checked = !checked;
    UIElement.SetColor(smk::Color::White);
    if(checked)
        UIElement.SetColor(smk::Color::Yellow);
}

smk::Text &Tile::getText(){
    return *text;
}

smk::Transformable &Tile::getTile() {
    return UIElement;
}
