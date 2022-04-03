#pragma once
#include <iostream>
#include <vector>

#include <smk/Shape.hpp>
#include <smk/Window.hpp>
#include <smk/Font.hpp>

#include "headers/Scene.hpp"

class GameMenu : public Scene {
private:
    std::string name = "GameMenuScene";
    smk::Window &window;
    smk::Font font = smk::Font("/resources/SHPinscher-Regular.otf", 96);
public:
    GameMenu(smk::Window&);
    ~GameMenu(){}
    void draw();
    void restart();
    std::string getName();
};