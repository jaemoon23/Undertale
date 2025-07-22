#pragma once
#include "Scene.h"
#include "Animator.h"
#include "BattleButton.h"
#include "StatusInBattleUI.h"
#include "Soul.h"

// 640, 480

class SceneBattle : public Scene
{
protected:
	// �ҿ� ��������Ʈ ( ���ϱ�, �޴� ���� )
	// json���� ������ ��������
	// ���ʹ� Ŭ����
	// �÷��̾� Ŭ����
	// ���� ���â
	// ��Ȳ ���� UI
	// �÷��̾� �������ͽ� UI
	// ��ư��
	sf::Sprite background;
	Soul* soul;
	sf::Sprite monster;
	sf::Sprite dialogueBox;

	sf::Text dialogue;

	sf::Text describe1;
	sf::Text describe2;
	sf::Text describe3;
	sf::Text describe4;
	sf::Text describe5;

	sf::RectangleShape describeBox;

	StatusInBattleUI* statusUI;
	BattleButton* fightButton;
	BattleButton* actButton;
	BattleButton* itemButton;
	BattleButton* mercyButton;

	Animator animator;

public:
	ButtonState btState = ButtonState::None;
	int btIndex = 0;

	SceneBattle();
	~SceneBattle() override = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	Soul* GetSoul() { return soul; }
};