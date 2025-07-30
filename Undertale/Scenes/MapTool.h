#pragma once
#include "Scene.h"
#include "Button.h"
#include "HitBox.h"

class TextGo;
class SpriteGo;

// 삭제 가능한 오브젝트를 하나로 다루기 위한 구조체
struct UndoAction
{
    enum class Type 
    { 
        Sprite,
        HitBox 
    } type;
    union 
    {
        SpriteGo* sprite;
        sf::RectangleShape* rect; 
    } data;
};

enum class HitBoxType
{
    Wall,
    Battle,
    Event,
    Door,
    Switch,
    Signs,
    SceneChanege,
    NextScene,
    PrevScene
};

struct HitBoxInfo
{
    sf::RectangleShape* shape;
    HitBoxType type;
    std::string field;
};

class MapTool :
    public Scene
{
protected:
    // 그리드
    sf::VertexArray grid;
    sf::Vector2f gridOffset;

    const int gridWidth = 640;
    const int gridHeight = 480;
    int cellSize = 32;
    int cellX;
    int cellY;

    bool gridDraw = false;

    sf::Vector2f windowSize;
   
    std::vector<UndoAction> undoStack;

    Button* hitBox = nullptr;
    Button* saveButton = nullptr;

    std::vector<Button*> objectButtons;
    std::vector<Button*> backgroundButtons;
   
    std::vector<SpriteGo*> objectSprites;
    std::vector<SpriteGo*> backgroundSprites;
    std::vector<SpriteGo*> placedSprites;

    HitBox hit;

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
       "graphics/back2.png",
       "graphics/back3.png",
       "graphics/back4.png",
       "graphics/back5.png",
       "graphics/back6.png",
       "graphics/SansBack.png",
       "graphics/PapyrusBack.png"
    };

    sf::RectangleShape dragHitBox;
    std::vector<HitBoxInfo> hitBoxes;
    sf::Vector2f dragStartPos;

    TextGo* hitBoxText;
    TextGo* saveBoxText;
    TextGo* backText;
    TextGo* objectText;

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


    void jsonInput();

};

