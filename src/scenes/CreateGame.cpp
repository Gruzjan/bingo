#include <iostream>
#include <string>

#include <smk/Color.hpp>
#include <smk/Shape.hpp>
#include <smk/Window.hpp>
#include <smk/Input.hpp>
#include <smk/Rectangle.hpp>
#include <smk/Vertex.hpp>
#include <smk/VertexArray.hpp>
#include <smk/Text.hpp>

#include "headers/CreateGame.hpp"
#include "headers/Button.hpp"
#include "headers/InputBox.hpp"
#include "headers/SceneManager.hpp"
#include "headers/Tile.hpp"

CreateGame::CreateGame(smk::Window &window) : window(window) {
  this->inputBox = new InputBox(60, 150, 350, 820, window, 48);
  listener = window.input().MakeCharacterListener();
  board = new Board(1250, 150, 0, 0, window);
}

void CreateGame::draw() {
  inputBox->onClick();

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
  backBtnTxt.SetPosition(backBtn.getX(), backBtn.getY());

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
      && inputBox->getInputText().size() > 0) 
        inputBox->pushBackPassword(inputBox->getInputText());      
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

  size4Btn.onClick([&]{board->setSize(4);});
  size5Btn.onClick([&]{board->setSize(5);});

  smk::Text size4BtnTxt = smk::Text(font, "4x4");
  size4BtnTxt.SetPosition(size4Btn.getX(), size4Btn.getY());
  size4BtnTxt.SetColor(smk::Color::White);

  smk::Text size5BtnTxt = smk::Text(font, "5x5");
  size5BtnTxt.SetPosition(size5Btn.getX(), size5Btn.getY());
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

    freeTileYesBtn.onClick([&]{board->setFreeTile(true);});
    freeTileNoBtn.onClick([&]{board->setFreeTile(false);});
    
    smk::Text freeTileYesBtnTxt = smk::Text(font, "Yes");
    freeTileYesBtnTxt.SetPosition(freeTileYesBtn.getX(), freeTileYesBtn.getY());
    freeTileYesBtnTxt.SetColor(smk::Color::White);

    smk::Text freeTileNoBtnTxt = smk::Text(font, "No");
    freeTileNoBtnTxt.SetPosition(freeTileNoBtn.getX(), freeTileNoBtn.getY());
    freeTileNoBtnTxt.SetColor(smk::Color::White);

    window.Draw(freeTileTitle);
    freeTileYesBtn.draw();
    freeTileNoBtn.draw();
    window.Draw(freeTileYesBtnTxt);
    window.Draw(freeTileNoBtnTxt);
  }else
    board->setFreeTile(false);
  //====== PRESETS ======
  smk::Text bingoPresetsTitle = smk::Text(font, "Bingo presets");
  bingoPresetsTitle.SetPosition(535, 300);
  bingoPresetsTitle.SetColor(smk::Color::White);

  Button cleanPresetBtn(525, 375, 250, 80, window);
  Button lysyPresetBtn(525, 490, 250, 80, window);
  Button wengrzynPresetBtn(525, 605, 250, 80, window);

  // cleanPresetBtn.onClick([&]{});
  // lysyPresetBtn.onClick([&]{});
  // wengrzynPresetBtn.onClick([&]{});

  smk::Text cleanPresetBtnTxt = smk::Text(font, "Empty");
  cleanPresetBtnTxt.SetPosition(cleanPresetBtn.getX(), cleanPresetBtn.getY());
  cleanPresetBtnTxt.SetColor(smk::Color::White);

  smk::Text lysyPresetBtnTxt = smk::Text(font, "Lysy");
  lysyPresetBtnTxt.SetPosition(lysyPresetBtn.getX(), lysyPresetBtn.getY());
  lysyPresetBtnTxt.SetColor(smk::Color::White);

  smk::Text wengrzynPresetBtnTxt = smk::Text(font, "Wengrzyn");
  wengrzynPresetBtnTxt.SetPosition(wengrzynPresetBtn.getX(), wengrzynPresetBtn.getY());
  wengrzynPresetBtnTxt.SetColor(smk::Color::White);
  
  window.Draw(bingoPresetsTitle);
  cleanPresetBtn.draw();
  lysyPresetBtn.draw();
  wengrzynPresetBtn.draw();
  window.Draw(cleanPresetBtnTxt);
  window.Draw(lysyPresetBtnTxt);
  window.Draw(wengrzynPresetBtnTxt);
  //====== PREVIEW ======
  smk::Text previewTitle = smk::Text(font, "Preview");
  previewTitle.SetPosition(1500, 95);
  previewTitle.SetColor(smk::Color::White);

  if(board->getSize() == 5 || board->getSize() == 4)
    board->draw();

  window.Draw(previewTitle);
  //====== GAME CODE ======
  smk::Text gameCodeTitle = smk::Text(font, "Game code");
  gameCodeTitle.SetPosition(window.width() / 2 - 80, 775);
  gameCodeTitle.SetColor(smk::Color::White);

  std::string gameCode = "ABCDEF";// = generateCode();
  smk::Text gameCodeTxt = smk::Text(font, gameCode);
  gameCodeTxt.SetPosition(window.width() / 2 - 50, 825);
  gameCodeTxt.SetColor(smk::Color::Yellow);

  window.Draw(gameCodeTitle);
  window.Draw(gameCodeTxt);
  //====== CREATE BUTTON ======
  Button createBtn(window.width() / 2 - 100, 900, 200, 100, window);
  createBtn.onClick([&] {
    SceneManager::updateName("GameMasterScene");
  });
  createBtn.draw();

  smk::Text createBtnTxt = smk::Text(font, "Create");
  createBtnTxt.SetPosition(createBtn.getX(), createBtn.getY());
  createBtnTxt.SetColor(smk::Color::White);
  window.Draw(createBtnTxt);
}

//====== OTHER FUNCTIONS ======

void CreateGame::restart() {}

std::string CreateGame::getName() {
  return this->name;
}