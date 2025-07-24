#pragma once
#include "GameObject.h"
#include "Animator.h"

class Enemy : public GameObject
{
protected:
	sf::Sprite sprite;
	Animator animator;

	int hp;

	// 총알 공격 패턴
	// 몬스터 대사 모음

public:
	Enemy(const std::string& name = "");
	virtual ~Enemy() = default;

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

