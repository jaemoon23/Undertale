#pragma once
#include "GameObject.h"
#include "Animator.h"
#include "HitBox.h"

class HpUi;
class Sans;
class DialogueBox;
class UiChanger;
class InventoryUi;
class Player : public GameObject
{
protected:
	sf::Sprite body;
	std::wstring name = L"플레이어";
	int maxHp = 10;
	int hp = 10;
	int att = 0;
	int def = 0;
	int exp = 0;
	int gold = 0;

	float speed = 80.f;
	sf::Vector2f direction;

	Animator animator;
	HitBox hitBox;

	Sans* sans;
	HpUi* hpui;
	DialogueBox* dialoguebox;
	UiChanger* uichanger;
	InventoryUi* inventoryui;
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

	void SetHp(int h) { hp = h; }
	void SetAtt(int a) { att = a; }
	void SetDef(int d) { def = d; }
	void SetGold(int g) { gold = g; }
	void SetExp(int e) { exp = e; }
	void SetName(const std::wstring& n) { name = n; }

	void SansInteract();

	void SetSans(Sans* s) { sans = s; }
	void SetBox(DialogueBox* dbox) { dialoguebox = dbox; }
	void SetInventoryUi(InventoryUi* i) { inventoryui = i; }
	void SetUiChanger(UiChanger* u) { uichanger = u; }	
};

