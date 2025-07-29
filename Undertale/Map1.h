#pragma once
#include "Scene.h"
#include <fstream>
#include "json.hpp"
#include "SpriteGo.h"
#include "test.h"
class Player;

class Map1 : public Scene
{
protected:
	float battleCheckTimer = 0.f;
	const float battleCheckInterval = 1.f;
	test test;
	SpriteGo* background1 = nullptr;
	Player* player;
	std::vector<SpriteGo*> testObjects;
	std::vector<HitBoxInfo1> hitboxes;

	sf::RectangleShape wall;
	sf::Vector2f direction;
	float eventMoveRemaining = 0.f;
	float eventMoveSpeed = 200.f; // �ʴ� �̵� �ӵ�
	float moveStep;

	bool wallHitBox = true;
	bool event = false;
	bool moveEvent = false;
	bool puzzleSuccess = false;

public:
	Map1();
	~Map1() override = default;

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	

};

