#pragma once
#include <smk/Window.hpp>
#include <smk/Shape.hpp>
#include <smk/Font.hpp>

#include "headers/Scene.hpp"
#include "headers/InputBox.hpp"

class GameMaster : public Scene {
private:
    std::string name = "GameMasterScene";
    smk::Window &window;
    smk::Font font = smk::Font("/resources/SHPinscher-Regular.otf", 48);
    std::map<std::string, bool> words;
    std::vector<std::string> wordKeys;
    InputBox *inputBox;
    int page;
public:
    GameMaster(smk::Window&);
    ~GameMaster() {};
    void draw();
    void restart();
    std::string getName();
};