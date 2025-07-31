#pragma once
#include "GameObject.h"
#include "Animator.h"
#include "HitBox.h"

class Papyrus : public GameObject
{
protected:
	sf::Sprite papyrus;
	std::string papyrustexIds = "Sprites/spr_papyrus_cape_0.png";

	
	HitBox hitBox;
public:
	Animator animator;
	Papyrus(const std::string& name = "");
	virtual ~Papyrus() = default;

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

	const sf::RectangleShape& GetHitBox() const;
};

