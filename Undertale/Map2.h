#pragma once
#include "Scene.h"
#include <fstream>
#include "json.hpp"
#include "SpriteGo.h"

class Player;
struct HitBoxInfo3
{
    sf::RectangleShape* shape;
    std::string type;
};
class Map2 :
    public Scene
{
protected:
    SpriteGo* background2 = nullptr;
    Player* player;
    std::vector<SpriteGo*> testObjects;
    std::vector<HitBoxInfo3> hitboxes;

    float battleCheckTimer = 0.f;
    const float battleCheckInterval = 1.f;
public:
    Map2();
    ~Map2() override = default;

    void Init() override;
    void Enter() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;
};

