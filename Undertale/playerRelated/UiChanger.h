#pragma once
#include "GameObject.h"

enum class SelectedText
{
	Inventory,
	Stat
};

class Player;
class InventoryUi;
class PlayerInfoUi;

class UiChanger : public GameObject
{
protected:
	bool isActive = false; 
	sf::Font font;
	std::string fonttexIds = "fonts/DungGeunMo.ttf";

	sf::Sprite uiChanger;
	std::string uiChangertexIds = "Sprites/backgroundui.png";

	sf::RectangleShape line;
	
	sf::Text invenText;
	sf::Text statText;

	int selectIndex = 0;

	Player* player;
	InventoryUi* inventoryui;
	PlayerInfoUi* playerinfoui;
public:
	UiChanger(const std::string& name = "");
	virtual ~UiChanger() = default;

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
	void SetPlayer(Player* p) { player = p; }
	void SetInventoryUi(InventoryUi* i) { inventoryui = i; }
	void SetPlayerInfoUi(PlayerInfoUi* info) { playerinfoui = info; }
	bool GetActive() {return isActive; }
};

