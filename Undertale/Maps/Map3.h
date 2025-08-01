#pragma once
#include "Scene.h"
#include "SpriteGo.h"
#include "TalkObject.h"
#include "TextWindow.h"

class Player;
class InventoryUi;
class DialogueBox;
class UiChanger;
class PlayerInfoUi;
class HealItem;
class PlayerInfo;

class Map3 : public Scene
{
protected:
	float battleCheckTimer = 0.f;
	const float battleCheckInterval = 1.f;

	std::vector<SpriteGo*> objects;
	std::vector<HitBoxInfo1> hitboxes;

	SpriteGo* background = nullptr;
	Player* player;
	UiChanger* uichanger;
	InventoryUi* inventoryui;
	DialogueBox* dialoguebox;
	PlayerInfoUi* playerinfoui;

	bool puzzleSuccess = false;

	sf::Vector2f startPos = { 214.f,267.f };

	TalkObject* spaghetti;
	TalkObject* microwave;
	TalkObject* notepaper;
	TalkObject* mousehole;
	TalkObject* savepoint;
	TextWindow* textWindow;

public:
	Map3();
	~Map3() override = default;

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

