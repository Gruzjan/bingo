#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <codecvt>
#include <random>
#include <algorithm>
#include <boost/algorithm/string/join.hpp>
#include <emscripten.h>

#include <smk/Color.hpp>
#include <smk/Shape.hpp>
#include <smk/Window.hpp>
#include <smk/Input.hpp>
#include <smk/Font.hpp>
#include <smk/Text.hpp>

#include "headers/GameView.hpp"
#include "headers/SceneManager.hpp"

EM_ASYNC_JS(bool, checkwin, (const char * words), {
  const options = {
    method: "post",
    headers: {
      'Accept': 'application/json',
      'Content-Type': 'application/json'
    },
    body: JSON.stringify({
      words: UTF8ToString(words)
    })
  };
  const res = await fetch("http://localhost:3000/checkwin", options);
  const test = await res.json();
  console.log(test);
  const text = test["won"];

  return text
});

GameView::GameView(smk::Window &window) :window(window) {
  board = new Board(window.width() / 2 - 450, 150, 0, 0, window);
}

void GameView::draw() {
  if(!boardReady)
    setBoard(5, true, passwords); // this should come from game creator // it came :O
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
    if (board->isBingo()) {
      std::vector<std::string> tempWords;
      for (auto x : board->getWinningWords()) {
        std::string tempStr = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(x);
        boardReady = false;
        tempWords.push_back(tempStr);
      }
      std::string joinedString = boost::algorithm::join(tempWords, ";");
      std::cerr << joinedString << std::endl;
      bool isWon = checkwin(joinedString.c_str());
      std::cerr << isWon << std::endl;
      if (isWon) {
        board->uncheckAll();
        std::random_shuffle(passwords.begin(), passwords.end());
        std::cerr << "won?" << std::endl;
      }
    }
    //send to backend // sent
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
      if(x->getPassword().size() < 10)
        x->getText().SetPosition(x->getX(), x->getY() + 175 / 2 - font.line_height() / 2);
      else{
        x->getText().SetPosition(x->getX(), x->getY());
        if(x->getPassword().size() < 18)
          x->getText().SetString(x->getPassword().substr(0, 8) + L"-\n" + x->getPassword().substr(8, 9));
        else
          x->getText().SetString(x->getPassword().substr(0, 8) + L"-\n" + x->getPassword().substr(8, 9) + L"\n...");
      }
      x->getText().SetColor(smk::Color::Black);
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

bool GameView::checkTransfer() {
  return this->isTransfered;
}

void GameView::transferData(nlohmann::json j) {
  this->nickname = j["username"];
  this->gameCode = j["gameCode"];
  for (std::string x : j["words"]) {
    std::wstring tempStr = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(x);
    passwords.push_back(tempStr);
  }
  std::cerr << gameCode << std::endl;
  std::random_shuffle(passwords.begin(), passwords.end());
  isTransfered = true;
}