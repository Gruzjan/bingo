#pragma once
#include <iostream>
#include <vector>

#include <smk/Shape.hpp>
#include <smk/Window.hpp>
#include <smk/Font.hpp>

#include "headers/Scene.hpp"
#include "headers/InputBox.hpp"

class CreateGame : public Scene {
private:
    std::string name = "CreateGameScene";
    smk::Window &window;
    smk::Font font = smk::Font("/resources/SHPinscher-Regular.otf", 48);
    InputBox *inputBox;
    smk::Input::CharacterListener listener;
    //wchar_t character;
    std::vector<std::wstring> passwords;

public:
    CreateGame(smk::Window&);
    ~CreateGame(){}
    void draw();
    void restart();
    std::string getName();
};