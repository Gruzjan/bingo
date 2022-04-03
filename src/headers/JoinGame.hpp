#pragma once
#include <iostream>
#include <vector>

#include <smk/Shape.hpp>
#include <smk/Window.hpp>

#include "headers/Scene.hpp"
#include "headers/InputBox.hpp"

class JoinGame : public Scene {
private:
    std::string name = "JoinGameScene";
    smk::Font font = smk::Font("/resources/SHPinscher-Regular.otf", 48);
    smk::Window &window;
    InputBox username;
    InputBox gamecode;
public:
    JoinGame(smk::Window&);
    void draw();
    void restart();
    std::string getName();
};