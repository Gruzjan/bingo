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
  username(InputBox(750, 400, 450, 100, window, 72)),
  gamecode(InputBox(750, 600, 450, 100, window, 72)) {}

void JoinGame::draw() {
  Button joinBtn(750, 750, 450, 125, window);
  Button backBtn(0, 0, 180, 100, window);

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
  username.drawRaw();

  gamecode.onClick();
  gamecode.writeListener([&] {});
  gamecode.drawRaw();

  auto usernameText = smk::Text(font, L"Username");
  usernameText.SetPosition(username.getX(), username.getY()-75);
  window.Draw(usernameText);

  auto codeText = smk::Text(font, L"Game code");
  codeText.SetPosition(gamecode.getX(), gamecode.getY()-75);
  window.Draw(codeText);

  auto exitSymbol = smk::Text(font, L"|<-");
  window.Draw(exitSymbol);

  auto joinText = smk::Text(font, L"Join Game");
  joinText.SetPosition(joinBtn.getX(), joinBtn.getY());
  window.Draw(joinText);
}

void JoinGame::restart() {}

std::string JoinGame::getName() {
  return this->name;
}
