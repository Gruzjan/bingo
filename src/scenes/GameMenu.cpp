#include <iostream>
#include <fstream>

#include <smk/Color.hpp>
#include <smk/Shape.hpp>
#include <smk/Window.hpp>
#include <smk/Input.hpp>
#include <smk/Rectangle.hpp>
#include <smk/Vertex.hpp>
#include <smk/VertexArray.hpp>
#include <smk/Font.hpp>
#include <smk/Text.hpp>

#include "headers/GameMenu.hpp"
#include "headers/Button.hpp"
#include "headers/SceneManager.hpp"

GameMenu::GameMenu(smk::Window &window) :window(window) {}

void GameMenu::draw() {
  Button createBtn(1000, 500, 450, 125, window);
  Button joinBtn(500, 500, 450, 125, window);

  joinBtn.onClick([&] {
    SceneManager::updateName("JoinGameScene");
  });

  createBtn.onClick([&] {
    SceneManager::updateName("CreateGameScene");
  });

  auto text = smk::Text(font, "Lysy Bingo The Game");
  text.SetPosition(600, 300);

  auto joinText = smk::Text(font, "Join Game");
  joinText.SetPosition(joinBtn.getX() + 50, joinBtn.getY() + 20);

  auto createText = smk::Text(font, "Create Game");
  createText.SetPosition(createBtn.getX() + 20, createBtn.getY() + 20);

  window.Draw(text);
  joinBtn.draw();
  createBtn.draw();
  window.Draw(joinText);
  window.Draw(createText);
}

void GameMenu::restart() {
  std::cout<<"test";
}

std::string GameMenu::getName() {
  return this->name;
}