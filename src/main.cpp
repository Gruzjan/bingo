#include <smk/Color.hpp>
#include <smk/Shape.hpp>
#include <smk/Window.hpp>

#include "scenes/GameMenu.cpp"
#include "scenes/JoinGame.cpp"
#include "utils/SceneManager.cpp"

std::string SceneManager::sceneName = "";

int main() {
  auto window = smk::Window(640, 480, "scena1");
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
