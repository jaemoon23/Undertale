#pragma once
#include "Scene.h"
#include "SpriteGo.h"

class Player;
class Papyrus;
class InventoryUi;
class DialogueBox;
class UiChanger;
class PlayerInfoUi;
class HealItem;
class PlayerInfo;

class MapPapyrus : public Scene
{
protected:
	float battleCheckTimer = 0.f;
	const float battleCheckInterval = 1.f;

	std::vector<SpriteGo*> objects;
	std::vector<HitBoxInfo1> hitboxes;
	sf::Font font;

	SpriteGo* background = nullptr;
	Player* player;
	Papyrus* papyrus;

	UiChanger* uichanger;
	InventoryUi* inventoryui;
	DialogueBox* dialoguebox;
	PlayerInfoUi* playerinfoui;

	SpriteGo* exclamationmark;

	sf::RectangleShape doorwall;

	bool puzzleSuccess = false;
	bool dialogueTriggered = false;
	bool dialogueEnd = false; // 파피루스 대화 종료 시 움직일 수 있게 
	bool isexclamationmarkActive = false;
	bool BattleEnd = false;
	bool papyrusImageChange = false;
	bool papyrusLastInteract = false;

	bool papyrusMercy = false;
	bool mercyDialogEnd = false;
	float exclamationmarkTimer = 0.f;

	bool playerRun = false;
	bool isDoor = true;
public:
	MapPapyrus();
	~MapPapyrus() override = default;

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

