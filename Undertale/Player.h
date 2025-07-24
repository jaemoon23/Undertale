#pragma once
#include "GameObject.h"
#include "Animator.h"
#include "HitBox.h"

class HpUi;
class Sans;
class DialogueBox;
class Player : public GameObject
{
protected:
	sf::Sprite body;
	std::string name = "Chara";
	int maxHp = 10;
	int hp = 10;
	int att = 10;
	int def = 10;


	float speed = 50.f;
	sf::Vector2f direction;

	Animator animator;
	HitBox hitBox;

	Sans* sans;
	HpUi* hpui;
	DialogueBox* dialoguebox;
	

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
	void SetAtt(int a) { att = a; }
	void SetDef(int d) { def = d; }
	void SetName(const std::string& n) { name = n; }

	void SansInteract();

	void SetHpUi(HpUi* hpui);
	void SetSans(Sans* s) { sans = s; }
	void SetBox(DialogueBox* dbox) { dialoguebox = dbox; }
	
};

