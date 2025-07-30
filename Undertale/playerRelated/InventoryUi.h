#pragma once
#include "GameObject.h"

enum class SelectedItem
{
	healItem1,
	healItem2,
	healItem3,
	healItem4,
};

class Player;
class HealItem;
class DialogueBox;
class PlayerInfo;
class InventoryUi : public GameObject
{
protected:
	int selectIndex = 0;
	//bool isActive = true;

	sf::Sprite inventory;
	sf::Font fonts;
	std::string fonttexIds = "fonts/DungGeunMo.ttf";
	std::string inventorytexIds ="Sprites/backgroundui.png";

	sf::RectangleShape square;
	sf::RectangleShape line;

	sf::Text inventext;
	sf::Text boxtext;
	sf::Text text;

	sf::Text itemText1;
	sf::Text itemText2;
	sf::Text itemText3;
	sf::Text itemText4;

	sf::Sprite selectSprite;
	std::string selecttexIds = "Sprites/spr_heart_battle_pl_0.png";

	Player* player;
	DialogueBox* dialoguebox;
	PlayerInfo* playerinfo;

public:
	static HealItem healItem[4];

	InventoryUi(const std::string& name = "");
	virtual ~InventoryUi() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;
	void SetPlayer(Player* p) { player = p; }
	Player* GetPlayer() const { return player; }
	//void SetHealItem1(HealItem* item) { healItem1 = item; }
	void SetBox(DialogueBox* db) { dialoguebox = db; }

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

