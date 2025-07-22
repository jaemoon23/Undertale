#pragma once
#include "Scene.h"
class SceneBattle : public Scene
{
protected:
	sf::Sprite enemySprite;
	// ���� ���â
	// ��Ȳ ���� UI
	// �÷��̾� �������ͽ� UI
	// ��ư��

public:
	SceneBattle();
	~SceneBattle() override = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

