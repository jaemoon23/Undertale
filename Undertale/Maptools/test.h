#pragma once
#include "Scene.h"
#include "SpriteGo.h"

class test :
    public Scene
{
protected:
    SpriteGo* background = nullptr;
    std::vector<SpriteGo*> testObjects;

    sf::Vector2f windowSize = { 640.f,480.f };
public:
    test();
    ~test() override = default;

    void Init() override;
    void Enter() override;
    void Update(float dt) override;
    void Exit() override;
    void Draw(sf::RenderWindow& window) override;
};

