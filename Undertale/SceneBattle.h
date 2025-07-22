#pragma once
#include "Scene.h"
#include "Animator.h"
#include "BattleButton.h"
#include "StatusInBattleUI.h"

// 1280, 960

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
	sf::Sprite soul;
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
	BattleButton* attackButton;

	Animator animator;

public:
	SceneBattle();
	~SceneBattle() override = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};