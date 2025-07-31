#pragma once
#include "Scene.h"
#include "SpriteGo.h"

class Player;

class MapSans : public Scene
{
protected:
	sf::Sprite sans;

	float battleCheckTimer = 0.f;
	const float battleCheckInterval = 1.f;

	std::vector<SpriteGo*> testObjects;
	std::vector<HitBoxInfo1> hitboxes;

	SpriteGo* background = nullptr;
	Player* player;

	bool puzzleSuccess = false;

	const int columnCount = 8;
	std::vector<sf::Sprite> column;

	bool isSansEvent = false;
	float timer = 0.f;
	float waitingTime = 1.5f;
	float screenMoveTime = 3.5f;

	bool isSansTalking = false;
	sf::Sprite textWindow;
	sf::Sprite sansFace;
	sf::Text text;

public:
	MapSans();
	~MapSans() override = default;

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetColumn();
};

