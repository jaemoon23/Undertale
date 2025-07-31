#pragma once
#include "Scene.h"
#include "SpriteGo.h"

class Player;

class MapSans :
    public Scene
{
protected:
	float battleCheckTimer = 0.f;
	const float battleCheckInterval = 1.f;

	std::vector<SpriteGo*> testObjects;
	std::vector<HitBoxInfo1> hitboxes;

	SpriteGo* background = nullptr;
	Player* player;

	bool puzzleSuccess = false;

	const int columnCount = 5;
	std::vector<sf::Sprite> column;

public:
	MapSans();
	~MapSans() override = default;

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

