#pragma once
#include "Scene.h"

class Player;
class SceneTest : public Scene
{
protected:
	Player* player;
public:
	SceneTest();
	~SceneTest() override = default;
	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

