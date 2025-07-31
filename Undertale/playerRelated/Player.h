#pragma once
#include "GameObject.h"
#include "Animator.h"
#include "HitBox.h"
#include "Map1.h"
#include "PlayerInfo.h"

class HpUi;
class Sans;
class DialogueBox;
class UiChanger;
class InventoryUi;
class PlayerInfoUi;
class HealItem;
class PlayerInfo;
class Player : public GameObject
{
protected:
	// LJM
	sf::Vector2f prevPosition;

	std::string texId = "Sprites/idle.png";
	sf::Sprite body;
	sf::Sprite soul;
	sf::Sprite battleSymbol;
	std::wstring name;

	float speed = 96.f;
	sf::Vector2f direction;

	//Animator animator;
	HitBox hitBox;

	Sans* sans;
	HpUi* hpui;
	DialogueBox* dialoguebox;
	UiChanger* uichanger;
	InventoryUi* inventoryui;
	PlayerInfoUi* playerInfoUi;
	HealItem* healItem;
	PlayerInfo playerInfo;
	

	bool move = true;

	sf::RectangleShape blackBackground;
	sf::Vector2f destVec = { 0.f,0.f };
	Scene* scene = nullptr;
	float timer = 0;
	float soulBlinkTimer = 0.f;
	float symbolExistTime = 0.7f;
	float soulBlinkTime = 0.5f;
	float soulMoveTime = 1.0f;
	bool isBattleEnter = false;
	bool isDrawSymbol = false;
	bool isDrawSoul = false;
	bool isSoulMove = false;
public:
	bool isSansMap = false;
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

	Animator animator;
	
	int GetHp() const { return PlayerInfo::hp; }
	int GetMaxHp() const { return PlayerInfo::maxHp; }

	void SansInteract();
	void SansSecondsInteract();
	void PapyrusInteract();
	void PapyrusBattleEndInteract();

	void SetSans(Sans* s) { sans = s; }
	void SetBox(DialogueBox* dbox) { dialoguebox = dbox; }
	void SetInventoryUi(InventoryUi* i) { inventoryui = i; }
	void SetUiChanger(UiChanger* u) { uichanger = u; }
	void SetPlayerInfoUi(PlayerInfoUi* infoUi) { playerInfoUi = infoUi; }

	void SetHealItem(HealItem* item) { healItem = item; }

	const sf::RectangleShape& GetHitBox() const;
	sf::Vector2f getPos() { return prevPosition; }

	sf::Sprite& GetSprite() { return body; }
	void SetMove(bool a);
	void SetColorBlack() { body.setColor(sf::Color::Black); }
	void StartBattle();

	void SetAnimatorStop() { animator.Stop(); }
};

