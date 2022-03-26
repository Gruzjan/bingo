#include <iostream>

#include <smk/Color.hpp>
#include <smk/Shape.hpp>
#include <smk/Window.hpp>
#include <smk/Input.hpp>
#include <smk/Rectangle.hpp>
#include <smk/Vertex.hpp>
#include <smk/VertexArray.hpp>

#include "headers/CreateGame.hpp"
#include "headers/Button.hpp"
#include "headers/SceneManager.hpp"

CreateGame::CreateGame(smk::Window &window) : window(window) {}

void CreateGame::draw() {
  Button textbox(250, 250, 110, 40, window);
  Button createBtn(250, 350, 110, 40, window);
  Button backBtn(0, 0, 80, 40, window);

  createBtn.onClick([&] {
    SceneManager::updateName("menu");
  });

  backBtn.onClick([&] {
    SceneManager::updateName("GameMenuScene");
  });

  createBtn.draw();
  textbox.draw();
  backBtn.draw();
}

void CreateGame::restart() {}

std::string CreateGame::getName() {
  return this->name;
}