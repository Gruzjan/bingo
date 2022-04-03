#include <iostream>
#include <fstream>
#include <string>

#include <smk/Color.hpp>
#include <smk/Shape.hpp>
#include <smk/Window.hpp>
#include <smk/Input.hpp>
#include <smk/Font.hpp>
#include <smk/Text.hpp>

#include "headers/GameView.hpp"
#include "headers/SceneManager.hpp"

GameView::GameView(smk::Window &window) :window(window) {
  board = new Board(window.width() / 2 - 450, 150, 0, 0, window);
}

void GameView::draw() {
  if(!boardReady)
    setBoard(5, true, {L"Energol", L"\"Przerwa jest\"", L"\"To jest proste\"",
                                                            L"\"Mikisheesh\"", L"\"Wlochaty\"", L"\"Panie technik\"",
                                                            L"Praca w grupach", L"Uwaga za mundur", L"Pompki",
                                                            L"\"Lendzionek\"", L"\"Czego?\"", L"\"Co tam brzeczysz?\"",
                                                            L"\"Dzieci\"", L"Zapowiedzana kartkowka", L"Zapowiedziany sprawdzian",
                                                            L"Grzybowski incydent", L"Narzekanie na mazak", L"Musi byc C++",
                                                            L"Zla nieobecnosc", L"*Puszcza film*", L"\"Nie psuj mi ...!\"",
                                                            L"\"Krzesla!\"", L"Lagodniejsze traktowanie kobiet",
                                                            L"Muzyka w tle", L"*Slychac klucze*", L"Godzina wychowawcza",
                                                            L"Problem z pendrivem", L"Absurdalna uwaga", L"Absurdalna pochwala"}); // this should come from game creator
  board->setTilesOnClickAction();
  //====== SCENE TITLE ======
  auto sceneTitle = smk::Text(font, "The lysy bingo game");
  sceneTitle.SetPosition(window.width() / 2 - 175, 50);
  sceneTitle.SetColor(smk::Color::White);

  window.Draw(sceneTitle);
  //====== BACK BUTTON ======
  Button backBtn(0, 0, 120, 60, window);
  backBtn.onClick([&] {
    SceneManager::updateName("GameMenuScene");
  });

  smk::Text backBtnTxt = smk::Text(font, "Back");
  backBtnTxt.SetPosition(backBtn.getX() + 20, backBtn.getY() + backBtn.height / 2 - font.line_height() / 2);

  backBtn.draw();
  window.Draw(backBtnTxt);
  //====== GAME INFO ======
  auto gameCodeText = smk::Text(font, gameCode);
  gameCodeText.SetPosition(0, 80);
  gameCodeText.SetColor(smk::Color::Yellow);

  auto nicknameText = smk::Text(font, nickname);
  nicknameText.SetPosition(0, 80 + font.line_height());
  nicknameText.SetColor(smk::Color::White);

  window.Draw(gameCodeText);
  window.Draw(nicknameText);
  //====== BINGO BUTTON ======
  Button bingoBtn(1600, 510, 120, 60, window);
  bingoBtn.UIElement.SetColor(smk::Color::Grey);
  bingoBtn.onClick([&] {
    //send to backend
  });

  smk::Text bingoBtnTxt = smk::Text(font, "Bingo");
  bingoBtnTxt.SetColor(smk::Color::Black);
  bingoBtnTxt.SetPosition(bingoBtn.getX() + 10, bingoBtn.getY() + bingoBtn.height / 2 - font.line_height() / 2);

  if(board->isBingo())
    bingoBtn.UIElement.SetColor(smk::Color::White);
  
  bingoBtn.draw();
  window.Draw(bingoBtnTxt);

  //====== BOARD ======
  if(boardReady){
    board->draw(false);
    for(auto x : board->getTiles()){
      x->setText(new smk::Text(font, x->getPassword()));
      x->getText().SetColor(smk::Color::Black);
      x->getText().SetPosition(x->getX(), x->getY());
      window.Draw(x->getText());
    }
  }
}

void GameView::setPasswords(std::vector<std::wstring> passwords){
  this->passwords = passwords;
}

void GameView::setGameCode(std::string gameCode){
  this->gameCode = gameCode;
}

void GameView::setNickname(std::string nickname){
  this->nickname = nickname;
}

void GameView::setBoard(Board &board){
  this->board = &board;
  boardReady = true;
}

void GameView::setBoard(int size, bool freeTile, std::vector<std::wstring> passwords){
  board->setSize(size);
  board->setFreeTile(freeTile);
  board->setPasswords(passwords);
  setPasswords(passwords);
  
  boardReady = true;
}

void GameView::restart() {
}

std::string GameView::getName() {
  return this->name;
}