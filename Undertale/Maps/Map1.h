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

	SpriteGo* background = nullptr;
	Player* player = nullptr;
	std::vector<SpriteGo*> objects;
	std::vector<HitBoxInfo1> hitboxes;

	sf::RectangleShape wall;
	sf::Vector2f direction;
	float eventMoveRemaining = 0.f;
	float eventMoveSpeed = 200.f; // 초당 이동 속도
	float moveStep;


	std::wstring fullText = L"* 스위치는 하나 뿐이다.";
	std::wstring currentText = L"";
	bool isText = false;
	float textTimer = 0.f;
	float textSpeed = 0.05f; // 글자당 시간 (초)
	int currentIndex = 0;
	float time = 0.f;

	bool wallHitBox = true;
	bool event = false;
	bool moveEvent = false;
	bool puzzleSuccess = false;

	SpriteGo* textWindow = nullptr;
	SpriteGo* textWindow2 = nullptr;
	TextGo* text = nullptr;
	TextGo* text2 = nullptr;

	UiChanger* uichanger;
	InventoryUi* inventoryui;
	DialogueBox* dialoguebox;
	PlayerInfoUi* playerinfoui;

	bool showText = false;

	sf::Vector2f startPos = { -9.f,-61.f };
public:
	Map1();
	~Map1() override = default;

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

