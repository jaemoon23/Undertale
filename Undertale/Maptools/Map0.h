#pragma once
#include "Scene.h"
#include "SpriteGo.h"

struct HitBoxInfo1
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

class Map0 :
    public Scene
{
protected:
    float battleCheckTimer = 0.f;
    const float battleCheckInterval = 1.f; 

   
    SpriteGo* background = nullptr;
    Player* player;
    std::vector<SpriteGo*> testObjects;
    std::vector<HitBoxInfo1> hitboxes;

    sf::Vector2f playerPos = { 0.f, 0.f };
    sf::Vector2f windowSize = { 640.f,480.f };

    Sans* sans;

    UiChanger* uichanger;
    InventoryUi* inventoryui;
    DialogueBox* dialoguebox;
    PlayerInfoUi* playerinfoui;
public:
    Map0();
    ~Map0() override = default;

    Player* GetPlayer() { return player; }
    void Init() override;
    void Enter() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;
};

