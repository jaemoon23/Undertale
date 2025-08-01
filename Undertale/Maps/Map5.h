#pragma once
#include "Scene.h"
#include "SpriteGo.h"
class Player;
class TextGo;

class InventoryUi;
class DialogueBox;
class UiChanger;
class PlayerInfoUi;
class HealItem;
class PlayerInfo;

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
	UiChanger* uichanger;
	InventoryUi* inventoryui;
	DialogueBox* dialoguebox;
	PlayerInfoUi* playerinfoui;

	bool puzzleSuccess = false;

	TextGo* textQ;
	TextGo* textW;
	TextGo* textE;
	TextGo* textR;

	bool battle = true;
	bool ran = true;
	int r = 0;
	float maxTime = 1.f;
	float currentTime = 0.f;

	float maxTime2 = 1.f;
	float currentTime2 = 0.f;

	sf::Vector2f startPos = { 78.f,248.f };
public:
	Map5();
	~Map5() override = default;

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void GenerateRandomKeySequence(float dt);

};

