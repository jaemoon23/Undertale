#pragma once
#include "Scene.h"
#include "SpriteGo.h"
class Player;

class Map4 :
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
public:
	Map4();
	~Map4() override = default;

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

