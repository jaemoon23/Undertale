#pragma once
#include "Scene.h"
#include "Animator.h"
#include "BattleButton.h"
#include "StatusInBattleUI.h"
#include "Soul.h"
#include "json.hpp"
#include "Bullet.h"
using json = nlohmann::json;

// 640, 480
class BattleDialogueBox;
class BattleBox;

class SceneBattle : public Scene
{
protected:
	sf::Sprite background;
	Soul* soul;

	sf::Sprite monster;
	std::string monsterTexId;

	BattleDialogueBox* dialBox;

	BattleBox* btBox;

	StatusInBattleUI* statusUI;

	BattleButton* fightButton;
	BattleButton* actButton;
	BattleButton* itemButton;
	BattleButton* mercyButton;

	Animator animator;

	sf::Vector2f size = { 640.f,480.f };

	float dialTimer = 0.f;
	const float dialExistTime = 2.f;

	float turnTimer = 0.f;
	float turnDuration;

	json data;

	int PatternIndex = 0;
	int patternCount = 0;
	std::vector<Bullet*> bulletTemp;

public:
	bool isMyTurn = true;
	ButtonState btState = ButtonState::None;
	int btIndex = 0;
	int actChooseIndex = 0;
	int actChooseCount = 0;
	int lineIndex = 0;
	int lineCount = 2;
	int monsterHp = 100;
	int monsterMaxHp = 100;

	SceneBattle();
	~SceneBattle() override = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	Soul* GetSoul() { return soul; }
	StatusInBattleUI* GetStatusUI() { return statusUI; }

	void SetMonsterTurn();
	void SetPlayerTurn();

	void SetActDescribe();
};