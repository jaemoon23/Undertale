#pragma once
#include "GameObject.h"
#include "HitBox.h"
#include "Soul.h"
#include "Animator.h"

class SceneBattle;

class Bullet : public GameObject
{
protected:
	sf::Sprite sprite;
	sf::RectangleShape beam;
	HitBox hitBox;
	HitBox beamHitBox;;
	Animator animator;

	SceneBattle* scene;
	Soul* soul;

	std::string texId = "graphics/spr_eggbullet.png";

	sf::Vector2f pos = { 200.f, 200.f };
	sf::Vector2f dir = { 1.f, 1.f };

	float moveSpeed = 100.f;
	float rotationSpeed = 180.f;

	float timer = 0.f;
	float beamTimer = 0.f;
	float tickTimer = 0.f;
	float tickTime = 0.1f;
	float beamTime = 1.0f;
	float waitingTime = 1.5f;
	float splitStartTime = 1.0f;
	float aniDelayTime = 1.0f;

	int damage = 4;

	bool isHoming = false;
	bool isAnimation = false;
	bool isDraw = false;

public:
	std::string aniId = "";
	sf::Vector2f splitDir = { 0.f,0.f };
	BulletPattern pattern = BulletPattern::Normal;
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

