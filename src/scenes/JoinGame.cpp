#include <iostream>

#include <smk/Color.hpp>
#include <smk/Shape.hpp>
#include <smk/Window.hpp>
#include <smk/Input.hpp>
#include <smk/Rectangle.hpp>
#include <smk/Vertex.hpp>
#include <smk/VertexArray.hpp>
#include <smk/Text.hpp>
#include <emscripten.h>
#include <boost/algorithm/string/split.hpp> 
#include <boost/algorithm/string/classification.hpp>

#include "headers/JoinGame.hpp"
#include "headers/Button.hpp"
#include "headers/SceneManager.hpp"
#include "headers/InputBox.hpp"
#include "headers/HTTPClient.hpp"
#include "nlohmann/json.hpp"

EM_ASYNC_JS(char *, join, (const char * code), {
  const options = {
    method: "post",
    headers: {
      'Accept': 'application/json',
      'Content-Type': 'application/json'
    },
    body: JSON.stringify({
      gameCode: UTF8ToString(code)
    })
  };
  const res = await fetch("http://localhost:3000/join", options);
  const test = await res.json();
  console.log(test);
  const text = test["words"];
  var lengthBytes = lengthBytesUTF8(text)+1;
  var stringOnWasmHeap = _malloc(lengthBytes);
  stringToUTF8(text, stringOnWasmHeap, lengthBytes);

  return stringOnWasmHeap;
});

JoinGame::JoinGame(smk::Window &window) 
  : window(window), 
  username(InputBox(750, 400, 450, 100, window, 72)),
  gamecode(InputBox(750, 600, 450, 100, window, 72)) {}

void JoinGame::draw() {
  Button joinBtn(750, 750, 450, 125, window);
  Button backBtn(0, 0, 180, 100, window);

  joinBtn.onClick([&] {
    std::string temp = gamecode.getInputString();
    const char *code = temp.c_str();
    char *res = join(code);
    std::string words = res;
    if (words.size() > 0) {
      this->setPasswords(words);
      SceneManager::updateName("GameViewScene");
    }
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

void JoinGame::setPasswords(std::string raw) {
  boost::split(passwords, raw, boost::is_any_of(";"), boost::token_compress_on);
}

std::vector<std::string> JoinGame::getPasswords() {
  return this->passwords;
}

std::string JoinGame::getUsername() {
  return username.getInputString();
}

std::string JoinGame::getGameCode() {
  return gamecode.getInputString();
}
