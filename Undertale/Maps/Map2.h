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
    std::vector<HitBoxInfo1> hitboxes;

    sf::RectangleShape wall;

    float battleCheckTimer = 0.f;
    const float battleCheckInterval = 1.f;

    Sans* sans;
    UiChanger* uichanger;
    InventoryUi* inventoryui;
    DialogueBox* dialoguebox;
    PlayerInfoUi* playerinfoui;

    float imageChangeTimer = 0.f;
    int currentImageIndex = 0;
    std::vector<sf::Texture*> images; // 교체할 이미지들
    std::vector<sf::Texture*> sansimages;

    int playerImageIndex = 0;
    int sansImageIndex = 0;

    bool animationPlay = false;
    bool InteractedSans = false;
    bool firstInteractedEnds = false;
    bool imageChangedOnce = false;

    float afterTurnTimer = 0.f;
    bool charaTurn = false;

    float reactivateTimer = 0.f;
    bool reactivated = false; // 플레이어와 샌즈가 다시 active 할때 

    float sansSecondInteractTimer = 0.f; // 샌즈와 다시 대화할 때 
    bool isWaitingSansSecondInteract = false;
    bool wallDisabled = false;

public:

    Map2();
    ~Map2() override = default;

    void Init() override;
    void Enter() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;
};

