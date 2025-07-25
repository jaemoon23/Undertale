#pragma once
#include "GameObject.h"

class HealItem : public GameObject
{
protected:
	std::wstring itemName;
	int healAmount = 0;

public:
	HealItem(const std::string& name = "", int healAmount = 1);
	virtual ~HealItem() = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	int GetHealAmount() const { return healAmount; } // Èú·®À» ¹ÝÈ¯
	std::wstring GetItemText() const { return itemName; }
};

