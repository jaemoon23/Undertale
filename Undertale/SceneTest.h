#pragma once
#include "Scene.h"

class Player;
class Sans;
class BackGroundUi;
class TestBackGround;
class HpUi;
class NameUi;

class SceneTest : public Scene
{
protected:
	Player* player;
	Sans* sans;
	BackGroundUi* backgroundui;
	TestBackGround* testbackground;
	HpUi* hpui;
	NameUi* nameui;
public:
	SceneTest();
	~SceneTest() override = default;
	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

