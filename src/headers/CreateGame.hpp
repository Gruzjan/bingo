#pragma once
#include <iostream>
#include <vector>

#include <smk/Shape.hpp>
#include <smk/Window.hpp>
#include <smk/Font.hpp>

#include "headers/Scene.hpp"

class CreateGame : public Scene {
private:
    std::string name = "CreateGameScene";
    smk::Window &window;
    smk::Font font = smk::Font("/resources/SHPinscher-Regular.otf", 48);
public:
    GameMenu(smk::Window&);
    ~GameMenu(){}
    void draw();
    void restart();
    std::string getName();
};