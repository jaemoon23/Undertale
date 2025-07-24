#pragma once
#include "Scene.h"
#include "Button.h"

class TextGo;
class SpriteGo;

class MapTool :
    public Scene
{
protected:
    sf::Vector2f windowSize;
    sf::Vector2f defaultCenter;

    Button* hitBox;

    std::vector<Button*> objectButtons;
    std::vector<Button*> backgroundButtons;
   
    std::vector<SpriteGo*> objectSprites;
    std::vector<SpriteGo*> backgroundSprites;
    std::vector<SpriteGo*> placedSprites;

    SpriteGo* activeSprite = nullptr;
    SpriteGo* currentBackground = nullptr; 

    std::vector<std::string> objectTexturePaths = {
       "graphics/spr_f_maincharad_0.png",
       "graphics/spr_cutetable_0.png",
       "graphics/spr_darkelevator_l_0.png",
       "graphics/spr_darknesstotem_0.png"
    };
    std::vector<std::string> backgroundTexturePaths = {
       "graphics/bg_firstroom.png",
       "graphics/bg_innrooms_0.png"
    };

    sf::RectangleShape dragHitBox;
    std::vector<sf::RectangleShape> hitBoxes;
    sf::Vector2f dragStartPos;

    bool isDragging = false;
    bool dragMode = false;
public:
    MapTool();
    ~MapTool() override = default;
    
    void Init() override;
    void Enter() override;
    void Exit() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;
};

