#include <iostream>

#include <smk/Color.hpp>
#include <smk/Shape.hpp>
#include <smk/Window.hpp>
#include <smk/Input.hpp>
#include <smk/Rectangle.hpp>
#include <smk/Vertex.hpp>
#include <smk/VertexArray.hpp>

#include "headers/JoinGame.hpp"
#include "headers/Button.hpp"
#include "headers/SceneManager.hpp"

JoinGame::JoinGame(smk::Window &window) : window(window) {}

void JoinGame::draw() {
  Button joinBtn(250, 350, 110, 40, window);
  Button backBtn(0, 0, 80, 40, window);

  joinBtn.onClick([&] {
    SceneManager::updateName("GameViewScene");
  });

  backBtn.onClick([&] {
    SceneManager::updateName("GameMenuScene");
  });

  joinBtn.draw();
  backBtn.draw();
}

void JoinGame::restart() {}

std::string JoinGame::getName() {
  return this->name;
}