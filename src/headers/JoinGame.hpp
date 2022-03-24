#pragma once
#include <iostream>
#include <vector>

#include <smk/Shape.hpp>
#include <smk/Window.hpp>

#include "headers/Scene.hpp"

class JoinGame : public Scene {
private:
    std::string name = "JoinGameScene";
    smk::Window &window;
public:
    JoinGame(smk::Window&);
    void draw();
    void restart();
    std::string getName();
};