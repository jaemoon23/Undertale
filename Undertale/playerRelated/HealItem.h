#pragma once
#include <string>
#include "GameObject.h"

class HealItem : public GameObject 
{
private:
    std::wstring name;
    int healAmount;

public:
    HealItem();
    HealItem(const std::string& name, int healAmount);
    ~HealItem() override = default; 

    void SetInfo(std::wstring str, int amount) 
    {
        name = str;
        healAmount = amount;
    }

    void SetName(std::wstring str) { name = str; }
    std::wstring GetName() const { return name; }
    int GetHealAmount() const { return healAmount; }

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;    
};