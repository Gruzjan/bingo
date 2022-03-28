#include <smk/Color.hpp>
#include <smk/Shape.hpp>
#include <smk/Window.hpp>

#include "scenes/GameMenu.cpp"
#include "scenes/JoinGame.cpp"
#include "scenes/CreateGame.cpp"
#include "utils/SceneManager.cpp"
#include "utils/UIElement.cpp"
#include "utils/Button.cpp"
#include "utils/InputBox.cpp"

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
