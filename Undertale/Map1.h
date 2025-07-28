#pragma once
#include "Scene.h"
#include <fstream>
#include "json.hpp"
#include "SpriteGo.h"
#include "test.h"
class Player;

struct HitBoxInfo2
{
	sf::RectangleShape* shape;
	std::string type;
};
class Map1 : public Scene
{
protected:
	test test;
	SpriteGo* background1 = nullptr;
	Player* player;
	std::vector<SpriteGo*> testObjects;
	std::vector<HitBoxInfo2> hitboxes;
public:
	Map1();
	~Map1() override = default;

	void SetPlayer(Player* player) { this->player = player; }
	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

