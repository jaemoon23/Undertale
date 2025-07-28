#pragma once
#include "GameObject.h"
#include "Animator.h"
#include "HitBox.h"

class HpUi;
class Sans;
class DialogueBox;
class UiChanger;
class InventoryUi;
class PlayerInfoUi;
class HealItem;

class Player : public GameObject
{
protected:
	// LJM
	sf::Vector2f prevPosition;

	std::string texId = "Sprites/idle.png";
	sf::Sprite body;
	std::wstring name;
	int maxHp = 0;
	int hp = 0;
	int att = 0;
	int def = 0;
	int exp = 0;
	int maxexp = 100;
	int gold = 0;
	int level = 0;

	float speed = 80.f;
	sf::Vector2f direction;

	Animator animator;
	HitBox hitBox;

	Sans* sans;
	HpUi* hpui;
	DialogueBox* dialoguebox;
	UiChanger* uichanger;
	InventoryUi* inventoryui;
	PlayerInfoUi* playerInfoUi;
	HealItem* healItem;


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

	void SetHp(int h);
	void SetAtt(int a);
	void SetDef(int d);
	void SetGold(int g);
	void SetLevel(int l);
	void SetExp(int e) { exp = e; }
	void SetName(const std::wstring& n);

	void SansInteract();

	void SetSans(Sans* s) { sans = s; }
	void SetBox(DialogueBox* dbox) { dialoguebox = dbox; }
	void SetInventoryUi(InventoryUi* i) { inventoryui = i; }
	void SetUiChanger(UiChanger* u) { uichanger = u; }	
	void SetPlayerInfoUi(PlayerInfoUi* infoUi) { playerInfoUi = infoUi; }

	void SetHealItem(HealItem* item) { healItem = item; }

	void UseHealItem(HealItem* item);
	void Heal(int amount, int maxHp);
	void GetHealItem(const std::string& healitemName);

	const sf::RectangleShape& GetHitBox() const;
	sf::Vector2f getPos() { return prevPosition; }	
};

