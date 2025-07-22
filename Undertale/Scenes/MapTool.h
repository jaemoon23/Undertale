#pragma once
#include "Scene.h"
#include "Button.h"


class MapTool :
    public Scene
{
protected:
    Button* b1;
    
public:
    MapTool();
    ~MapTool() override = default;
    
    void Init() override;
    void Enter() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;
};

