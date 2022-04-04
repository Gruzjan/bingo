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
    smk::Font font = smk::Font("/resources/SHPinscher-Regular.otf", 72);
    smk::Window &window;
    InputBox username;
    InputBox gamecode;
    std::vector<std::string> passwords;
public:
    JoinGame(smk::Window&);
    void draw();
    void restart();
    std::string getName();
    void setPasswords(std::string);
    std::vector<std::string> getPasswords();
    std::string getUsername();
    std::string getGameCode();
};