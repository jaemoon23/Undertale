#pragma once
#include "Scene.h"
#include "Button.h"
#include "InputText.h"

class TextGo;
class SpriteGo;

class MapTool :
    public Scene
{
protected:
    sf::Vector2f windowSize;

    TextGo* object;
    SpriteGo* back;
    
    std::vector<Button*> buttons;
    std::vector<SpriteGo*> sprites;

    SpriteGo* ch;
    sf::RectangleShape backSheets;
    sf::RectangleShape objectSheets;

    sf::VertexArray grid;
    sf::Vector2f gridOffset;

    const int gridWidth = 680;
    const int gridHeight = 480;
    int cellSize = 32;
    int cellX;
    int cellY;

    bool gridDraw = false;
    
public:
    MapTool();
    ~MapTool() override = default;
    
    void Init() override;
    void Enter() override;
    void Exit() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;

    void HandleZoom(float delta);
};

