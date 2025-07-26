#pragma once
#include "Scene.h"
#include "SpriteGo.h"
struct HitBoxInfos
{
    sf::RectangleShape* shape;
    std::string type; 
};

class Player;

class test :
    public Scene
{
protected:
    SpriteGo* background = nullptr;
    Player* player;
    std::vector<SpriteGo*> testObjects;
    std::vector<HitBoxInfos> hitboxes;

    sf::Vector2f playerPos = { 0.f, 0.f };
    sf::Vector2f windowSize = { 640.f,480.f };
public:
    test();
    ~test() override = default;

    void Init() override;
    void Enter() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;
};

