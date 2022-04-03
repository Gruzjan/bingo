#include <iostream>
#include <string>
#include <numeric>
#include <algorithm>
#include <locale>
#include <codecvt>

#include <smk/Color.hpp>
#include <smk/Shape.hpp>
#include <smk/Window.hpp>
#include <smk/Input.hpp>
#include <smk/Rectangle.hpp>
#include <smk/Vertex.hpp>
#include <smk/VertexArray.hpp>
#include <smk/Text.hpp>
#include <nlohmann/json.hpp>

#include "headers/CreateGame.hpp"
#include "headers/Button.hpp"
#include "headers/InputBox.hpp"
#include "headers/SceneManager.hpp"
#include "headers/Tile.hpp"
#include "headers/HTTPClient.hpp"

CreateGame::CreateGame(smk::Window &window) : window(window) {
  this->inputBox = new InputBox(60, 150, 350, 820, window, 48);
  srand(time(NULL));
  this->inputBox = new InputBox(60, 150, 350, 820, window, 48);
  listener = window.input().MakeCharacterListener();
  board = new Board(1250, 150, 0, 0, window);

  gameCode = generateCode();
}

void CreateGame::draw() {
  inputBox->onClick();
  board->setTilesOnClickAction();

  //====== SCENE TITLE ======
  smk::Text sceneTitle = smk::Text(font, "Game creator");
  sceneTitle.SetPosition(window.width() / 2 - 110, 30);
  sceneTitle.SetColor(smk::Color::Red);

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
  //====== INPUT SECTION ======
  auto inputTitleBg = smk::Shape::Square();
  inputTitleBg.SetScaleX(350);
  inputTitleBg.SetScaleY(60);
  inputTitleBg.SetPosition(60, 90);
  inputTitleBg.SetColor(smk::Color::Yellow);

  smk::Text inputTitle = smk::Text(font, "Passwords");
  inputTitle.SetPosition(350 / 2 - 20, 95);
  inputTitle.SetColor(smk::Color::White);

  if(board->getSize() != 5 && board->getSize() != 4)
    inputBox->setInputText(L"Select size first!");
  else if((board->getSize() == 5 || board->getSize() == 4) && inputBox->getInputText() == L"Select size first!")
    inputBox->setInputText(L"");
  else
    inputBox->writeListener([&] {
      if (window.input().IsKeyPressed(GLFW_KEY_ENTER) 
      && inputBox->getInputText().size() > 0) {
        inputBox->pushBackPassword(inputBox->getInputText());      
        board->setPasswords(inputBox->getPasswords());
      }
    });

  window.Draw(inputTitleBg);
  window.Draw(inputTitle);
  inputBox->draw();
  //====== SIZE SELECTION ======
  smk::Text sizeSelectionTitle = smk::Text(font, "Board size");
  sizeSelectionTitle.SetPosition(560, 95);
  sizeSelectionTitle.SetColor(smk::Color::White);

  Button size4Btn(525, 170, 100, 80, window);
  Button size5Btn(675, 170, 100, 80, window);

  if(board->getSize() == 4){
    size4Btn.UIElement.SetColor(smk::Color::Green);
    size5Btn.UIElement.SetColor(smk::Color::Blue);
  }else if(board->getSize() == 5){
    size4Btn.UIElement.SetColor(smk::Color::Blue);
    size5Btn.UIElement.SetColor(smk::Color::Green);
  }

  size4Btn.onClick([&]{board->setSize(4);});
  size5Btn.onClick([&]{board->setSize(5);});

  smk::Text size4BtnTxt = smk::Text(font, "4x4");
  size4BtnTxt.SetPosition(size4Btn.getX() + 20, size4Btn.getY() + size4Btn.height / 2 - font.line_height() / 2);
  size4BtnTxt.SetColor(smk::Color::White);

  smk::Text size5BtnTxt = smk::Text(font, "5x5");
  size5BtnTxt.SetPosition(size5Btn.getX() + 20, size5Btn.getY() + size5Btn.height / 2 - font.line_height() / 2);
  size5BtnTxt.SetColor(smk::Color::White);

  window.Draw(sizeSelectionTitle);
  size4Btn.draw();
  size5Btn.draw();
  window.Draw(size4BtnTxt);
  window.Draw(size5BtnTxt);
  //====== FREE TILE SETTINGS ======
  if(board->getSize() == 5){
    smk::Text freeTileTitle = smk::Text(font, "Make middle tile free?");
    freeTileTitle.SetPosition(825, 95);
    freeTileTitle.SetColor(smk::Color::White);

    Button freeTileYesBtn(890, 170, 100, 80, window);
    Button freeTileNoBtn(1040, 170, 100, 80, window);
    if(board->getFreeTile()){
      freeTileYesBtn.UIElement.SetColor(smk::Color::Green);
      freeTileNoBtn.UIElement.SetColor(smk::Color::Blue);
    }else{
      freeTileYesBtn.UIElement.SetColor(smk::Color::Blue);
      freeTileNoBtn.UIElement.SetColor(smk::Color::Red);
    }

    freeTileYesBtn.onClick([&]{board->setFreeTile(true);});
    freeTileNoBtn.onClick([&]{board->setFreeTile(false);});
    
    smk::Text freeTileYesBtnTxt = smk::Text(font, "Yes");
    freeTileYesBtnTxt.SetPosition(freeTileYesBtn.getX() + 20, freeTileYesBtn.getY() + freeTileYesBtn.height / 2 - font.line_height() / 2);
    freeTileYesBtnTxt.SetColor(smk::Color::White);

    smk::Text freeTileNoBtnTxt = smk::Text(font, "No");
    freeTileNoBtnTxt.SetPosition(freeTileNoBtn.getX() + 30, freeTileNoBtn.getY() + freeTileNoBtn.height / 2 - font.line_height() / 2);
    freeTileNoBtnTxt.SetColor(smk::Color::White);

    window.Draw(freeTileTitle);
    freeTileYesBtn.draw();
    freeTileNoBtn.draw();
    window.Draw(freeTileYesBtnTxt);
    window.Draw(freeTileNoBtnTxt);
  }else if(board->getSize() == 4)
    board->setFreeTile(false);
  //====== PRESETS ======
  smk::Text bingoPresetsTitle = smk::Text(font, "Bingo presets");
  bingoPresetsTitle.SetPosition(535, 300);
  bingoPresetsTitle.SetColor(smk::Color::White);

  Button cleanPresetBtn(525, 375, 250, 80, window);
  Button lysyPresetBtn(525, 490, 250, 80, window);
  Button numbersPresetBtn(525, 605, 250, 80, window);

  if(board->getSize() == 4 || board->getSize() == 5){
    cleanPresetBtn.onClick([&]{inputBox->clearPasswords();});
    lysyPresetBtn.onClick([&]{inputBox->setPasswords(presets["lysy"]);});
    numbersPresetBtn.onClick([&]{
      std::vector<int> temp(100);
      std::iota(temp.begin(), temp.end(), 1); // Set values 1 .. 100
      std::vector<std::wstring> numbersVec(100);  // Convert int vector to wstring vector
      std::transform(std::begin(temp), std::end(temp), std::back_inserter(numbersVec), [](int i) {return std::to_wstring(i);});
      presets.insert({"numbers", numbersVec});
      inputBox->setPasswords(presets["numbers"]);
    });
  }
  smk::Text cleanPresetBtnTxt = smk::Text(font, "Empty");
  cleanPresetBtnTxt.SetPosition(cleanPresetBtn.getX() + 80, cleanPresetBtn.getY() + cleanPresetBtn.height / 2 - font.line_height() / 2);
  cleanPresetBtnTxt.SetColor(smk::Color::White);

  smk::Text lysyPresetBtnTxt = smk::Text(font, "Lysy");
  lysyPresetBtnTxt.SetPosition(lysyPresetBtn.getX() + 90, lysyPresetBtn.getY() + lysyPresetBtn.height / 2 - font.line_height() / 2);
  lysyPresetBtnTxt.SetColor(smk::Color::White);

  smk::Text numbersPresetBtnTxt = smk::Text(font, "Numbers");
  numbersPresetBtnTxt.SetPosition(numbersPresetBtn.getX() + 60, numbersPresetBtn.getY() + numbersPresetBtn.height / 2 - font.line_height() / 2);
  numbersPresetBtnTxt.SetColor(smk::Color::White);
  
  window.Draw(bingoPresetsTitle);
  cleanPresetBtn.draw();
  lysyPresetBtn.draw();
  numbersPresetBtn.draw();
  window.Draw(cleanPresetBtnTxt);
  window.Draw(lysyPresetBtnTxt);
  window.Draw(numbersPresetBtnTxt);
  //====== PREVIEW ======
  smk::Text previewTitle = smk::Text(font, "Preview");
  previewTitle.SetPosition(1500, 95);
  previewTitle.SetColor(smk::Color::White);

  if(board->getSize() == 5 || board->getSize() == 4)
    board->draw(true);

  window.Draw(previewTitle);
  //====== GAME CODE ======
  smk::Text gameCodeTitle = smk::Text(font, "Game code");
  gameCodeTitle.SetPosition(window.width() / 2 - 80, 775);
  gameCodeTitle.SetColor(smk::Color::White);

  smk::Text gameCodeTxt = smk::Text(font, gameCode);
  gameCodeTxt.SetPosition(window.width() / 2 - 50, 825);
  gameCodeTxt.SetColor(smk::Color::Yellow);

  window.Draw(gameCodeTitle);
  window.Draw(gameCodeTxt);
  //====== CREATE BUTTON ======
  Button createBtn(window.width() / 2 - 100, 900, 200, 100, window);
  createBtn.onClick([&] {
    // It's very awkward but I don't have time to refactor this
    // Note to everyone: move stored passwords from
    // InputBox to this CreateGameScene
    this->setPasswords(inputBox->getPasswords());

    if ((board->getSize() == 4 || board->getSize() == 5) && this->getPasswords().size() > 5) {
      std::vector<std::string> passwordsString;
      for (std::wstring x : this->getPasswords()) {
        passwordsString.push_back(std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(x));
      }
      nlohmann::json data = {
        {"gameCode", this->gameCode},
        {"words", passwordsString},
        {"size", board->getSize()},
        {"freeTile", board->getFreeTile()}
      };
      std::cerr << data.dump() << std::endl;

      HTTPClient h("http://localhost:3000");
      h.fetch("POST", "/create", data);
      std::cerr << "backend hit" << std::endl;

      SceneManager::updateName("GameMasterScene");
    }
    else {
      std::cerr << "nuh uh" << std::endl;
    }
  });

  smk::Text createBtnTxt = smk::Text(font, "Create");
  createBtnTxt.SetPosition(createBtn.getX() + 50, createBtn.getY() + createBtn.height / 2 - font.line_height() / 2);
  createBtnTxt.SetColor(smk::Color::White);

  createBtn.draw();
  window.Draw(createBtnTxt);
}

//====== OTHER FUNCTIONS ======

void CreateGame::restart() {}

std::string CreateGame::getName() {
  return this->name;
}

std::string CreateGame::generateCode() {
  static const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  std::string result;
  result.reserve(6);
  for(int i = 0; i < 6; i++)
    result += alphabet[rand() % (sizeof(alphabet) - 1)];
  
  return result;
}

void CreateGame::setPasswords(std::vector<std::wstring> passwords) {
  this->passwords = passwords;
}

std::vector<std::wstring> CreateGame::getPasswords() {
  return passwords;
}

std::string CreateGame::getGameCode() {
  return gameCode;
}