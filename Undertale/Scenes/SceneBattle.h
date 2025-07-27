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
	sf::Vector2f monsterOriginalPos;
	std::string monsterTexId;
	std::string bgmId;

	BattleDialogueBox* dialBox;

	BattleBox* btBox;

	StatusInBattleUI* statusUI;

	BattleButton* fightButton;
	BattleButton* actButton;
	BattleButton* itemButton;
	BattleButton* mercyButton;

	Animator animator;
	std::string animationId;

	sf::Vector2f size = { 640.f,480.f };

	float dialTimer = 0.f;
	float dialExistTime = 0.f;

	float turnTimer = 0.f;
	float turnDuration;

	json data;
	json invenData;
	json itemData[4];
	int healAmount[4];

	int PatternIndex = 0;
	int patternCount = 0;
	std::vector<Bullet*> bulletTemp;

	bool isPlaying = true;

	sf::Color monsteroriginColor;
	sf::Color monsterblinkColor;
	float monsterblinkTimer = 0.f;
	float monsterblinkPeriodTimer = 0.f;
	const float monsterblinkPeriod = 0.15f;
	const float monsterblinkTime = 0.7f; 

	float monsterShakeTimer = 0.f;
	float monsterShakeInterval = 0.05f;

public:
	bool isMonsterShaking = false;
	bool isMonsterBlink = false;
	bool isMyTurn = true;
	ButtonState btState = ButtonState::None;
	int btIndex = 0;
	int actChooseIndex = 0;
	int actChooseCount = 0;
	int itemChooseIndex = 0;
	int itemChooseCount = 4;
	int mercyChooseIndex = 0;
	int lineIndex = 0;
	int lineCount = 2;
	int monsterHp = 100;
	int monsterMaxHp = 100;

	int playerATK = 50;
	int mercyPoint = 0;
	const int mercyCanPoint = 100;

	static std::string monsterJsonID;
	static SceneIds nextSceneId;

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

	void TryUseItem();
	void TryMercy();

	void MonsterBlinkUpdate(float dt);
	void MonsterDie();

	void PlayerDie();

	void SetBulletPattern();

	void MonsterShakeUpdate(float dt);
};