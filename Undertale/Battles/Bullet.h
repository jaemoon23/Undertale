#pragma once
#include "GameObject.h"
#include "HitBox.h"
#include "Soul.h"

class SceneBattle;

class Bullet : public GameObject
{
protected:
	sf::Sprite sprite;
	HitBox hitBox;

	SceneBattle* scene;
	Soul* soul;

	std::string texId = "graphics/spr_eggbullet.png";

	sf::Vector2f pos = { 200.f, 200.f };
	sf::Vector2f dir = { 1.f, 1.f };

	float moveSpeed = 100.f;

	float timer = 0.f;
	float waitingTime = 1.5f;

	int damage = 4;

public:
	Bullet(const std::string& name = "");
	virtual ~Bullet() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void SetBulletState(std::string tId, sf::Vector2f startPos, sf::Vector2f Dir, float speed, float waitTime, int damage);

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

