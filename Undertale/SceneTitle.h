#pragma once
#include "Scene.h"
class SceneTitle : public Scene
{
protected:
	sf::Sprite background;

	sf::Text text;
	
	sf::Vector2f size = { 320.f,240.f };

public:
	SceneTitle();
	~SceneTitle() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

