#include <iostream>

#include <smk/Window.hpp>
#include <nlohmann/json.hpp>

#include "headers/SceneManager.hpp"
#include "headers/GameMenu.hpp"
#include "headers/JoinGame.hpp"
#include "headers/CreateGame.hpp"
#include "headers/GameMaster.hpp"

SceneManager::SceneManager(smk::Window &window) : window(window) {
    Scene *menu = new GameMenu(window);
    Scene *join = new JoinGame(window);
    Scene *create = new CreateGame(window);
    Scene *master = new GameMaster(window);
    loadScene(menu);
    loadScene(join);
    loadScene(create);
    loadScene(master);
    currentScene = menu;
}

void SceneManager::setCurrentScene(int index) {
    currentScene = scenes[index];
}

void SceneManager::drawScene() {
    currentScene->draw();
}

void SceneManager::loadScene(Scene *scene) {
    scenesMap.insert(std::pair<std::string, Scene*>(scene->getName(), scene));
}

void SceneManager::updateScene() {
    if (scenesMap.find(sceneName) != scenesMap.end()) {
        currentScene = scenesMap[sceneName];
    }
}

void SceneManager::updateName(std::string name) {
    sceneName = name;
}

void SceneManager::dataPipeline() {
    if (sceneName == "GameMasterScene") {
        auto input = scenesMap.find("CreateGameScene")->second;
        CreateGame *c = dynamic_cast<CreateGame*>(input);
        auto output = scenesMap.find(sceneName)->second;
        GameMaster *g = dynamic_cast<GameMaster*>(output);
        if (!g->checkTransfer()) {
            nlohmann::json j = {
                {"gameCode", c->getGameCode()},
                {"passwords", c->getPasswords()},
            };
            g->transferData(j);
        }
   }
}
