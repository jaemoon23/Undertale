#pragma once
#include "GameObject.h"

class HealItem : public GameObject
{
protected:
	std::wstring name;
	int healAmount = 0;

public:
	HealItem(const std::string& name = "");
	virtual ~HealItem() = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

