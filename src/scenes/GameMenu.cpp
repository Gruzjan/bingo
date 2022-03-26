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
#include "utils/Button.cpp"
#include "headers/SceneManager.hpp"

GameMenu::GameMenu(smk::Window &window) :window(window) {}

void GameMenu::draw() {
  Button createBtn(350, 250, 110, 40, window);
  Button joinBtn(150, 250, 110, 40, window);

  const float margin = 60.f;

  joinBtn.onClick([&] {
    SceneManager::updateName("JoinGameScene");
  });

  createBtn.onClick([&] {
    return "CreateGameScene";
  });

  auto text = smk::Text(font, "The lysy bingo game");
  text.SetPosition(margin, margin);
  text.SetColor(smk::Color::White);

  window.Draw(text);
  joinBtn.draw();
  createBtn.draw();
}

void GameMenu::restart() {
  std::cout<<"test";
}

std::string GameMenu::getName() {
  return this->name;
}