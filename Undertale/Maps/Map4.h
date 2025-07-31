#pragma once
#include "Scene.h"
#include "SpriteGo.h"
#include "TextGo.h"

class Player;
class TemMie;
class InventoryUi;
class DialogueBox;
class UiChanger;
class PlayerInfoUi;
class HealItem;
class PlayerInfo;

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

	UiChanger* uichanger;
	InventoryUi* inventoryui;
	DialogueBox* dialoguebox;
	PlayerInfoUi* playerinfoui;

	bool puzzleSuccess = false;
	bool showText = false;

	



public:
	Map4();
	~Map4() override = default;

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

