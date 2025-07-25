#pragma once
#include "GameObject.h"
class Player;
class HealItem : public GameObject
{
protected:
	std::wstring name;
	int healAmount = 0;
	Player* player;	
public:
	HealItem(const std::string& name = "");
	virtual ~HealItem() = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetHealItem(int value) { healAmount = value; }
	void Use(Player* player);
};

