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

/*
void GameMenu(smk::Window &window) {
  Button createBtn(350, 250, 110, 40, window);
  Button joinBtn(150, 250, 110, 40, window);

  window.PoolEvents();
  window.Clear(smk::Color::Black);

  joinBtn.draw();
  createBtn.draw();
}
*/

GameMenu::GameMenu(smk::Window &window) :window(window) {
    std::string resource_path;
    std::vector<std::string> path_list = {
      // Code build and run inside ${CMAKE_CURRENT_DIRECTORY}/build
      "./resources",

      // Code build and run inside ${CMAKE_CURRENT_DIRECTORY}
      "../resources",

      // Code build for WebAssembly.
      "/resources",
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