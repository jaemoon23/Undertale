#pragma once
#include "TextGo.h"
class Player;
class NameUi : public TextGo
{
protected:
	bool isActive = false;
	std::string name = "Chara";

	Player* player;
public:
	NameUi(const std::string& fontIds = "", const std::string& name = "");
	~NameUi() = default;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetName(std::string name);
};

