#pragma once
#include "Scene.h"
#include "SpriteGo.h"

struct HitBoxInfos
{
    sf::RectangleShape* shape;
    std::string type;
};


class Player;
class Sans;
class InventoryUi;
class DialogueBox;
class UiChanger;
class PlayerInfoUi;
class HealItem;

class test :
    public Scene
{
protected:
    float battleCheckTimer = 0.f;
    const float battleCheckInterval = 1.f; 

   
    SpriteGo* background = nullptr;
    Player* player;
    std::vector<SpriteGo*> testObjects;
    std::vector<HitBoxInfos> hitboxes;

    sf::Vector2f playerPos = { 0.f, 0.f };
    sf::Vector2f windowSize = { 640.f,480.f };

    Sans* sans;

    UiChanger* uichanger;
    InventoryUi* inventoryui;
    DialogueBox* dialoguebox;
    PlayerInfoUi* playerinfoui;
    HealItem* healitem;
public:
    test();
    ~test() override = default;

    void Init() override;
    void Enter() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;
};

