#pragma once
#include "Scene.h"
#include "SpriteGo.h"
class Player;
class TextGo;

class Map5 :
	public Scene
{
protected:
	float battleCheckTimer = 0.f;
	const float battleCheckInterval = 1.f;

	std::vector<SpriteGo*> testObjects;
	std::vector<HitBoxInfo1> hitboxes;

	std::vector<sf::Keyboard::Key> targetKeys;

	SpriteGo* background = nullptr;
	Player* player;

	bool puzzleSuccess = false;

	TextGo* textQ;
	TextGo* textW;
	TextGo* textE;
	TextGo* textR;

	bool battle = true;
	bool ran = true;
	int r = 0;
	float maxTime = 5.f;
	float currentTime = 0.f;

	float maxTime2 = 5.f;
	float currentTime2 = 0.f;
public:
	Map5();
	~Map5() override = default;

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void GenerateRandomKeySequence(float dt);

};

