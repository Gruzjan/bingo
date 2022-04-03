#include <smk/Color.hpp>
#include <smk/Shape.hpp>
#include <smk/Window.hpp>
#include <smk/Input.hpp>
#include <smk/Sprite.hpp>
#include <smk/Audio.hpp>

#include "scenes/GameMenu.cpp"
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

nlohmann::json HTTPClient::HTTPResponseData = {};

std::string SceneManager::sceneName = "";

int main() {
  auto window = smk::Window(1920, 1080, "scena1");
  SceneManager manager(window);
  smk::Audio audio;

  auto texture = smk::Texture("/resources/background-pixel.png");
  auto background = smk::Shape::Square();
  background.SetTexture(texture);
  background.SetScaleX(1920);
  background.SetScaleY(1080);
  
  window.ExecuteMainLoop([&] {
    window.PoolEvents();
    window.Clear(smk::Color::Black);

    window.Draw(background);
    manager.updateScene();
    manager.dataPipeline();
    manager.drawScene();
    window.Display();
  });

  return EXIT_SUCCESS;
}
