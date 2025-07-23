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
class dialogueBox;
class BattleBox;

class SceneBattle : public Scene
{
protected:
	// 소울 스프라이트 ( 피하기, 메뉴 선택 )
	// json에서 데이터 가져오기
	// 에너미 클래스
	// 플레이어 클래스
	// 몬스터 대사창
	// 상황 묘사 UI
	// 플레이어 스테이터스 UI
	// 버튼들
	sf::Sprite background;
	Soul* soul;
	sf::Sprite monster;

	dialogueBox* dialBox;

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

	int PatternIndex = 1;
	int patternCount = 0;
	std::vector<Bullet*> bulletTemp;

public:
	bool isMyTurn = true;
	ButtonState btState = ButtonState::None;
	int btIndex = 0;
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
};