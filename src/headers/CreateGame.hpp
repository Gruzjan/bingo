#pragma once
#include <iostream>
#include <vector>
#include <map>

#include <smk/Shape.hpp>
#include <smk/Window.hpp>
#include <smk/Font.hpp>

#include "headers/Scene.hpp"
#include "headers/InputBox.hpp"
#include "headers/Board.hpp"


class CreateGame : public Scene {
private:
    std::string name = "CreateGameScene";
    std::string gameCode;
    smk::Window &window;
    smk::Font font = smk::Font("/resources/SHPinscher-Regular.otf", 48);
    InputBox *inputBox;
    smk::Input::CharacterListener listener;
    Board *board;
    std::map<std::string, std::vector<std::wstring>> presets {
                                                            {"lysy", {L"Energol", L"\"Przerwa jest\"", L"\"To jest proste\"",
                                                            L"\"Mikisheesh\"", L"\"Wlochaty\"", L"\"Panie technik\"",
                                                            L"Praca w grupach", L"Uwaga za mundur", L"Pompki",
                                                            L"\"Lendzionek\"", L"\"Czego?\"", L"\"Co tam brzeczysz?\"",
                                                            L"\"Dzieci\"", L"Zapowiedzana kartkowka", L"Zapowiedziany sprawdzian",
                                                            L"Grzybowski incydent", L"Narzekanie na mazak", L"Musi byc C++",
                                                            L"Zla nieobecnosc", L"*Puszcza film*", L"\"Nie psuj mi ...!\"",
                                                            L"\"Krzesla!\"", L"Lagodniejsze traktowanie kobiet",
                                                            L"Muzyka w tle", L"*Slychac klucze*", L"Godzina wychowawcza",
                                                            L"Problem z pendrivem", L"Absurdalna uwaga", L"Absurdalna pochwala"}}
        };
    std::vector<std::wstring> passwords;
public:
    CreateGame(smk::Window&);
    ~CreateGame(){}
    void draw();
    void restart();
    std::string generateCode();
    std::string getName();
    void setPasswords(std::vector<std::wstring>);
    std::vector<std::wstring> getPasswords();
    std::string getGameCode();
};