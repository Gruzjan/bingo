#include <iostream>

#include <smk/Color.hpp>
#include <smk/Shape.hpp>
#include <smk/Window.hpp>
#include <smk/Input.hpp>
#include <smk/Rectangle.hpp>
#include <smk/Vertex.hpp>
#include <smk/VertexArray.hpp>
#include <smk/Text.hpp>

#include "headers/JoinGame.hpp"
#include "headers/Button.hpp"
#include "headers/SceneManager.hpp"
#include "headers/InputBox.hpp"

JoinGame::JoinGame(smk::Window &window) 
  : window(window), 
  username(InputBox(700, 500, 300, 100, window)),
  gamecode(InputBox(700, 700, 300, 100, window)) {}

void JoinGame::draw() {
  Button joinBtn(700, 850, 300, 100, window);
  Button backBtn(0, 0, 100, 70, window);

  joinBtn.onClick([&] {
    SceneManager::updateName("menu");
  });

  backBtn.onClick([&] {
    SceneManager::updateName("GameMenuScene");
  });

  joinBtn.draw();
  backBtn.draw();

  username.onClick();
  username.writeListener([&] {});
}

void JoinGame::restart() {}

std::string JoinGame::getName() {
  return this->name;
}
