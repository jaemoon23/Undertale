#pragma once
#include "Scene.h"
#include "SpriteGo.h"

class Player;
class UiChanger;
class InventoryUi;
class DialogueBox;
class PlayerInfoUi;

class MapSans : public Scene
{
protected:
	sf::Sprite sans;

	float battleCheckTimer = 0.f;
	const float battleCheckInterval = 1.f;

	std::vector<SpriteGo*> objects;
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
	bool isDrawingText = false;
	sf::Sprite textWindow;
	sf::Sprite sansFace;
	sf::Text text;
	std::vector<std::wstring> sansLines;
	std::vector<std::string> sansFaceIds;
	std::vector<std::wstring> sansPeacefulLines;
	std::vector<std::string> sansPeacefulFaceIds;
	int lineIndex = 0;
	int lineCount;
	int peacefullLineIndex = 0;
	int peacefullLineCount;

	std::wstring tempLine;
	std::wstring currentLine;
	int charIndex = 0;
	float typeTimer = 0.f;
	float typeTime = 0.07f;

	float maxY;

	bool isEnd = false;
	float endTimer = 0.f;
	float endTime = 2.5f;

	bool isTalkEnd = false;
	bool isBattleEnter = false;

	// Moral이 point보다 작으면 전투 돌입
	const int JudgeMentPoint = 3;

	// 인벤토리 추가
	UiChanger* uichanger;
	InventoryUi* inventoryui;
	DialogueBox* dialoguebox;
	PlayerInfoUi* playerinfoui;
	sf::Vector2f uiViewCenter;
	//

	sf::Vector2f startPos = { -328.f,295.934f };

public:
	bool IsSansDie = false;
	MapSans();
	~MapSans() override = default;

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetColumn();

	void InventoryInit();
};

