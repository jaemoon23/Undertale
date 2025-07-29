#pragma once
#include "Scene.h"
#include <fstream>
#include "json.hpp"
#include "SpriteGo.h"


class Player;
class Sans;
class InventoryUi;
class DialogueBox;
class UiChanger;
class PlayerInfoUi;
class HealItem;

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

    sf::Font font;
    
    std::vector<SpriteGo*> testObjects;
    std::vector<HitBoxInfo3> hitboxes;

    sf::RectangleShape wall;

    float battleCheckTimer = 0.f;
    const float battleCheckInterval = 1.f;

    Sans* sans;
    UiChanger* uichanger;
    InventoryUi* inventoryui;
    DialogueBox* dialoguebox;
    PlayerInfoUi* playerinfoui;
public:
    bool animationPlay = false;

    Map2();
    ~Map2() override = default;

    void Init() override;
    void Enter() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;
};

