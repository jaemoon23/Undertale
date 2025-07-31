#pragma once
#include "Scene.h"
#include <fstream>
#include "json.hpp"
#include "SpriteGo.h"
#include "Map0.h"
class Player;
class TextGo;

class InventoryUi;
class DialogueBox;
class UiChanger;
class PlayerInfoUi;
class HealItem;
class PlayerInfo;

class Map1 : public Scene
{
protected:
	float battleCheckTimer = 0.f;
	const float battleCheckInterval = 1.f;
	Map0 Map0;
	SpriteGo* background1 = nullptr;
	Player* player;
	std::vector<SpriteGo*> testObjects;
	std::vector<HitBoxInfo1> hitboxes;

	sf::RectangleShape wall;
	sf::Vector2f direction;
	float eventMoveRemaining = 0.f;
	float eventMoveSpeed = 200.f; // 초당 이동 속도
	float moveStep;

	bool wallHitBox = true;
	bool event = false;
	bool moveEvent = false;
	bool puzzleSuccess = false;

	SpriteGo* textWindow = nullptr;
	TextGo* text = nullptr;

	UiChanger* uichanger;
	InventoryUi* inventoryui;
	DialogueBox* dialoguebox;
	PlayerInfoUi* playerinfoui;

	bool showText = false;
public:
	Map1();
	~Map1() override = default;

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	

};

