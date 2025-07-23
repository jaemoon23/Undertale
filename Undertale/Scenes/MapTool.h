#pragma once
#include "Scene.h"
#include "Button.h"
#include "InputText.h"


class MapTool :
    public Scene
{
protected:
    std::vector<Button*> buttons;

    Button* b1;
    Button* b2;

    InputText* t1;

    int test = 0;

    sf::RectangleShape backSheets;
    sf::RectangleShape objectSheets;

    sf::VertexArray grid;
    const int gridWidth = 640;
    const int gridHeight = 480;
    int cellSize = 32;
    
public:
    MapTool();
    ~MapTool() override = default;
    
    void Init() override;
    void Enter() override;
    void Exit() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;
};

