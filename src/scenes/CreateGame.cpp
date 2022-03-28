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
#include "headers/InputBox.hpp"
#include "headers/SceneManager.hpp"

CreateGame::CreateGame(smk::Window &window) : window(window) {}

void CreateGame::draw() {
  auto title = smk::Text(font, "Game creator");
  title.SetPosition(window.width() / 2 - 60, 30);
  title.SetColor(smk::Color::White);

  InputBox inputBox(60, 120, 350, 870, window);

  auto inputBg = smk::Shape::Square();
  inputBg.SetScaleX(350);
  inputBg.SetScaleY(30);
  inputBg.SetPosition(60, 90);
  inputBg.SetColor(smk::Color::Yellow);

  auto inputTitle = smk::Text(font, "Passwords");
  inputTitle.SetPosition(350 / 2 - 20, 95);
  inputTitle.SetColor(smk::Color::White);

  Button createBtn(250, 350, 110, 40, window);
  Button backBtn(0, 0, 120, 60, window);

  backBtn.onClick([&] {
    SceneManager::updateName("GameMenuScene");
  });

  window.Draw(inputBg);
  window.Draw(title);
  window.Draw(inputTitle);
  inputBox.draw();
  createBtn.draw();
  backBtn.draw();
}

void CreateGame::restart() {}

std::string CreateGame::getName() {
  return this->name;
}