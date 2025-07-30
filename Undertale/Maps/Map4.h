#pragma once
#include "Scene.h"
#include "SpriteGo.h"
#include "TextGo.h"

class Player;
class TemMie;

class Map4 :
    public Scene
{
protected:
	float battleCheckTimer = 0.f;
	const float battleCheckInterval = 1.f;

	std::vector<SpriteGo*> testObjects;
	std::vector<HitBoxInfo1> hitboxes;
	sf::RectangleShape wall;

	SpriteGo* textWindow = nullptr;
	SpriteGo* background = nullptr;
	

	TextGo* text = nullptr;
	Player* player;
	TemMie* temMie;

	bool puzzleSuccess = false;
	bool showText = false;

	// 아이템 샵
	int cost1 = 10; // 눈사탕 가격
	int cost2 = 15; // 쿠키 가격
	int cost3 = 20; // 아이스크림 가격
	int cost4 = 100000;



public:
	Map4();
	~Map4() override = default;

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

