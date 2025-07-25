#pragma once
#include "GameObject.h"
class TestBackGround : public GameObject
{
protected:
	sf::Sprite testbackground;
	std::string testtexIds = "Sprites/bg_asgore_livingroom_0.png";
public:
	TestBackGround(const std::string& name = "");
	virtual ~TestBackGround() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

