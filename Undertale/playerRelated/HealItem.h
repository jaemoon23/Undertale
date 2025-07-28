#pragma once
#include <string>
#include "GameObject.h"

class HealItem : public GameObject 
{
private:
    std::string name = "POTION";
    int healAmount;

public:
    HealItem(const std::string& name, int healAmount);
    ~HealItem() override = default; 

    std::string GetName() const { return name; }
    int GetHealAmount() const { return healAmount; }

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;    
};