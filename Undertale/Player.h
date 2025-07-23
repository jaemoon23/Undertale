#pragma once
#include "GameObject.h"
#include "Animator.h"
#include "HitBox.h"

class HpUi;
class Sans;
class Player : public GameObject
{
protected:
	sf::Sprite body;

	int maxHp = 0;
	int hp = 0;
	int att = 10;
	int def = 10;
	std::string name = "Chara";

	float speed = 200.f;
	sf::Vector2f direction;

	Sans* sans;
	HpUi* hpui;
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

	void SetHp(int h, int maxh);
	int GetHp() const { return hp; }
	void SetAtt(int a) { att = a; }
	int GetAtt() const { return att; }
	void SetDef(int d) { def = d; }
	int GetDef() const { return def; }

	void SetName(const std::string& n) { name = n; }
	const std::string& GetName() { return name; }

	void SetHpUi(HpUi* hpui);
	void SetSans(Sans* s) { sans = s; }

};

