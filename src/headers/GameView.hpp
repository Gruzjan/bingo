#pragma once
#include <iostream>
#include <vector>

#include <smk/Shape.hpp>
#include <smk/Window.hpp>
#include <smk/Font.hpp>

#include "headers/Board.hpp"
#include "headers/Scene.hpp"

class GameView : public Scene {
private:
    std::string name = "GameViewScene";
    smk::Window &window;
    smk::Font font = smk::Font("/resources/SHPinscher-Regular.otf", 48);
    bool boardReady = false;
    Board *board;
    std::vector<std::wstring> passwords; // backend or gamecreator
    std::string gameCode = "ABCEFG"; // backend
    std::string nickname = "Siema"; // backend (?)
public:
    GameView(smk::Window&);
    void setPasswords(std::vector<std::wstring>);
    void setNickname(std::string);
    void setGameCode(std::string);
    void setBoard(Board&);
    void setBoard(int, bool, std::vector<std::wstring>);
    ~GameView(){}
    void draw();
    void restart();
    std::string getName();
};