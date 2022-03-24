#pragma once

#include <iostream>
#include <map>
#include <vector>

#include <smk/Window.hpp>

#include "headers/Scene.hpp"

class SceneManager {
private:
    smk::Window &window;
    Scene *currentScene;
    std::vector<Scene*> scenes;
    std::map<std::string, Scene*> scenesMap;
    static std::string sceneName;

public:
    SceneManager(smk::Window&);
    void changeScene();
    void drawScene();
    Scene getCurrentScene();
    void setCurrentScene(int);
    void loadScene(Scene*);
    void updateScene();
    static void updateName(std::string);
};
