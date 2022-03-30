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

CreateGame::CreateGame(smk::Window &window) : window(window) {

  this->inputBox = new InputBox(60, 150, 350, 780, window);
  listener = window.input().MakeCharacterListener();

}

void CreateGame::draw() {
  auto sceneTitle = smk::Text(font, "Game creator");
  sceneTitle.SetPosition(window.width() / 2 - 60, 30);
  sceneTitle.SetColor(smk::Color::White);

  Button backBtn(0, 500, 120, 60, window);

  auto inputTitleBg = smk::Shape::Square();
  inputTitleBg.SetScaleX(350);
  inputTitleBg.SetScaleY(60);
  inputTitleBg.SetPosition(60, 90);
  inputTitleBg.SetColor(smk::Color::Yellow);

  auto inputTitle = smk::Text(font, "Passwords");
  inputTitle.SetPosition(350 / 2 - 20, 95);
  inputTitle.SetColor(smk::Color::White);


  Button createBtn(250, 350, 110, 40, window);
  inputBox->onClick();

  inputBox->writeListener([&] {
  if (window.input().IsKeyPressed(GLFW_KEY_ENTER) 
      && inputBox->getText().size() > 0) {
        passwords.push_back(inputBox->getText());

        for (auto x : passwords) {
            std::string temp(x.begin(), x.end());
            std::cerr << "Password: " << temp << std::endl;
        }
    }
  });

  backBtn.onClick([&] {
    SceneManager::updateName("GameMenuScene");
  });

  window.Draw(sceneTitle);
  inputBox->draw();
  window.Draw(inputTitleBg);
  window.Draw(inputTitle);
  createBtn.draw();
  backBtn.draw();
}

void CreateGame::restart() {}

std::string CreateGame::getName() {
  return this->name;
}