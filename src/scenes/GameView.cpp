#include <iostream>
#include <fstream>

#include <smk/Color.hpp>
#include <smk/Shape.hpp>
#include <smk/Window.hpp>
#include <smk/Input.hpp>
#include <smk/Font.hpp>
#include <smk/Text.hpp>

#include "headers/GameView.hpp"
#include "headers/SceneManager.hpp"

GameView::GameView(smk::Window &window) :window(window) {
    board = new Board(window.width() / 2 - 450, 150, 895, 895, window);
  };

  for (auto& path : path_list) {
    auto file = std::ifstream(path + "/bingo");
    if (!file)
      continue;

    std::string line;
    if (std::getline(file, line) && line == "bingo") {
      resource_path = path;
    }
  }
}

void GameView::draw() {
  if(!boardReady){
    setBoard(true, 5, {L"siema", L"eniu", L"lubie", L"placki"}); // this should come from game creator
    board->setTilesOnClickAction();
    std::cerr << "test" << std::endl; 
  }
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

  //====== REST ======
  if(boardReady)
    board->draw(false);
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

void GameView::setBoard(bool freeTile, int size, std::vector<std::wstring> passwords){
  board->setFreeTile(freeTile);
  board->setSize(size);
  board->setPasswords(passwords);
  setPasswords(passwords);
  
  boardReady = true;
}

void GameView::restart() {
}

std::string GameView::getName() {
  return this->name;
}