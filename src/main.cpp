#include <smk/Color.hpp>
#include <smk/Shape.hpp>
#include <smk/Window.hpp>
#include <smk/Input.hpp>
#include <smk/Sprite.hpp>
#include <smk/Audio.hpp>

#include "scenes/GameMenu.cpp"
#include "scenes/GameView.cpp"
#include "scenes/JoinGame.cpp"
#include "scenes/CreateGame.cpp"
#include "scenes/GameMaster.cpp"
#include "utils/SceneManager.cpp"
#include "utils/UIElement.cpp"
#include "utils/Button.cpp"
#include "utils/InputBox.cpp"
#include "utils/Tile.cpp"
#include "utils/Board.cpp"
#include <iostream>
#include "utils/HTTPClient.cpp"
#include <locale>
#include <codecvt>
#include <emscripten.h>

nlohmann::json HTTPClient::HTTPResponseData = {};

std::string SceneManager::sceneName = "";

EM_ASYNC_JS(char *, test, (const char * code), {
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
  const text = test["words"];
  var lengthBytes = lengthBytesUTF8(text)+1;
  var stringOnWasmHeap = _malloc(lengthBytes);
  stringToUTF8(text, stringOnWasmHeap, lengthBytes);

  return stringOnWasmHeap;
});

int main() {
  auto window = smk::Window(1920, 1080, "scena1");
  SceneManager manager(window);
  bool fetched = false;;

  auto texture = smk::Texture("/resources/background-pixel.png");
  auto background = smk::Shape::Square();
  background.SetTexture(texture);
  background.SetScaleX(1920);
  background.SetScaleY(1080);
  
  window.ExecuteMainLoop([&] {
    window.PoolEvents();
    window.Clear(smk::Color::Black);
    if(!fetched) {
      //std::string c = "ECIELY";
      //const char *code = c.c_str();
      //std::cerr << test(code) << std::endl;
      fetched = true;
    }

    window.Draw(background);
    manager.updateScene();
    manager.dataPipeline();
    manager.drawScene();
    window.Display();
  });

  return EXIT_SUCCESS;
}
