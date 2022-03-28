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
  Button createBtn(350, 250, 110, 40, window);
  Button joinBtn(150, 250, 110, 40, window);

  const float margin = 60.f;

  joinBtn.onClick([&] {
    SceneManager::updateName("JoinGameScene");
  });

  createBtn.onClick([&] {
    SceneManager::updateName("CreateGameScene");
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