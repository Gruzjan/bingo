#pragma once
class Scene {
public:
    Scene(){}
    virtual ~Scene(){}
    virtual void draw() = 0; 
    virtual void restart() = 0;
    virtual std::string getName() = 0;
};