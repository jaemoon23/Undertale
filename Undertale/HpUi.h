#pragma once
#include "TextGo.h"
class Player;
class HpUi : public TextGo
{
protected:
	bool isActive = false;
	int maxHp = 0;
	int hp = 0;

	Player* player;
public:
	HpUi(const std::string& fontIds ="", const std::string& name = "");
	~HpUi() = default;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetHp(int hp, int maxHp);
};

