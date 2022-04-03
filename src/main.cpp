#include <smk/Color.hpp>
#include <smk/Shape.hpp>
#include <smk/Window.hpp>
#include <smk/Input.hpp>

#include "scenes/GameMenu.cpp"
#include "scenes/JoinGame.cpp"
#include "scenes/CreateGame.cpp"
#include "utils/SceneManager.cpp"
#include "utils/UIElement.cpp"
#include "utils/Button.cpp"
#include "utils/InputBox.cpp"
#include "utils/Tile.cpp"
#include "utils/Board.cpp"
#include <iostream>
#include "utils/HTTPClient.cpp"

nlohmann::json HTTPClient::HTTPResponseData = {};

std::string SceneManager::sceneName = "";

int main() {
  auto window = smk::Window(1920, 1080, "scena1");
  SceneManager manager(window);
  
  window.ExecuteMainLoop([&] {
    window.PoolEvents();
    window.Clear(smk::Color::Black);
    
    manager.updateScene();
    manager.drawScene();
    window.Display();
  });

  return EXIT_SUCCESS;
}
