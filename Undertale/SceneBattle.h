#pragma once
#include "Scene.h"
class SceneBattle : public Scene
{
protected:
	sf::Sprite enemySprite;
	// 몬스터 대사창
	// 상황 묘사 UI
	// 플레이어 스테이터스 UI
	// 버튼들

public:
	SceneBattle();
	~SceneBattle() override = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

