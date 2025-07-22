#pragma once
#include "GameObject.h"
#include "HitBox.h"
class Sans : public GameObject
{
protected:
	sf::Sprite sans;
	std::string sanstexIds = "Sprites/spr_sans_sleep_0.png";

	HitBox hitBox;	
public:
	Sans(const std::string& name = "");
	virtual ~Sans() = default;

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

