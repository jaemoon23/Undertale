#pragma once
#include "GameObject.h"

class Player;
class HealItem;
class InventoryUi : public GameObject
{
protected:
	bool isActive = true;
	sf::Sprite inventory;
	sf::Font fonts;
	std::string fonttexIds = "fonts/DungGeunMo.ttf";
	std::string inventorytexIds ="Sprites/backgroundui.png";

	sf::RectangleShape square;
	sf::RectangleShape line;

	sf::Text inventext;
	sf::Text boxtext;
	sf::Text text;

	sf::Text itemText;

	Player* player;
	HealItem* healItem;
	
public:
	InventoryUi(const std::string& name = "");
	virtual ~InventoryUi() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;
	
	void SetHealItem(HealItem* item) { healItem = item; }

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

