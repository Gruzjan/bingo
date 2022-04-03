#pragma once
#include <smk/Window.hpp>
#include <smk/Shape.hpp>
#include <smk/Font.hpp>
#include <nlohmann/json.hpp>

#include "headers/Scene.hpp"
#include "headers/InputBox.hpp"

class GameMaster : public Scene {
private:
    std::string name = "GameMasterScene";
    smk::Window &window;
    smk::Font font = smk::Font("/resources/SHPinscher-Regular.otf", 48);
    std::map<std::string, bool> passwords;
    std::vector<std::string> wordKeys;
    InputBox *inputBox;
    int page;
    bool isTransfered = false;
    std::string gameCode;
public:
    GameMaster(smk::Window&);
    ~GameMaster() {};
    void draw();
    void restart();
    std::string getName();
    void transferData(nlohmann::json);
    bool checkTransfer();
};