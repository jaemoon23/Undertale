#pragma once
#include "GameObject.h"
#include "Animator.h"
#include "HitBox.h"

class Sans;
class Player : public GameObject
{
protected:
	sf::Sprite body;

	Sans* sans;

	float speed = 200.f;
	sf::Vector2f direction;
	//sf::Vector2f look;

	Animator animator;
	HitBox hitBox;

public:
	Player(const std::string& name = "");
	virtual ~Player() = default;

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

	void SetSans(Sans* s) { sans = s; }

};

