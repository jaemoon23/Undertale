#pragma once
#include "Scene.h"
class test :
    public Scene
{
public:
    test();
    ~test() override = default;

    void Init() override;
    void Enter() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;
};

