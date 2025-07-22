#pragma once
#include "GameObject.h"
#include "HitBox.h"

class SceneBattle;

class Soul : public GameObject
{
protected:
	sf::Sprite sprite;
	HitBox hitBox;

	int hp = 20;
	int maxHp = 20;

	float moveSpeed = 50.f;

	SceneBattle* scene;
	int* btIndex;

	sf::Vector2f size = { 640.f, 480.f };
	int minX;
	int maxX;
	int minY;
	int maxY;

public:

	Soul(const std::string& name = "");
	virtual ~Soul() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	sf::FloatRect GetGlobalBounds() const override { return sprite.getGlobalBounds(); }

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

