#pragma once
#include "GameObject.h"
#include "HitBox.h"

class SceneBattle;

class Soul : public GameObject
{
protected:
	sf::Sprite sprite;
	sf::Sprite shield;
	HitBox hitBox;

	float moveSpeed = 125.f;

	SceneBattle* scene;
	int* btIndex;
	int* actChooseIndex;
	int* actChooseCount;
	int* itemChooseIndex;
	int* itemChooseCount;
	int* mercyChooseIndex;

	sf::Vector2f size = { 640.f, 480.f };
	int minX;
	int maxX;
	int minY;
	int maxY;

	sf::Color originColor;
	sf::Color blinkColor;
	sf::Color shieldOriginColor;

	float blinkTimer = 0.f;
	float blinkPeriodTimer = 0.f;
	const float blinkPeriod = 0.15f;
	const float blinkTime = 1.f;

	float shieldblinkTimer = 0.f;
	const float shieldblinkTime = 0.1f; 

	float gravity = 600.f;
	float maxJumpPower = 320.f;
	float velocityY = 0.f;
	float jumpHoldTime = 0.f;
	float minJumpHoldTime = 0.1f;
	float maxJumpHoldTime = 0.33f;

public:
	int hp = 20;
	int maxHp = 20;
	bool isBlink = false;
	bool isShieldBlink = false;
	bool CanMove = true;
	bool isGravity = false;
	bool CanJump = false;

	Soul(const std::string& name = "");
	virtual ~Soul() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void SetTexture(std::string texId) { sprite.setTexture(TEXTURE_MGR.Get(texId)); }
	void SetShieldBlink()
	{ 
		shield.setColor(sf::Color::Red);
		isShieldBlink = true;
	}

	sf::FloatRect GetGlobalBounds() const override { return sprite.getGlobalBounds(); }
	sf::FloatRect GetShieldGlobalBounds() { return shield.getGlobalBounds(); }

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetBoundary(sf::FloatRect bounds);

	void TakeDamage(int damage);

	void BlinkUpdate(float dt);
	void ShieldBlinkUpdate(float dt);
};

