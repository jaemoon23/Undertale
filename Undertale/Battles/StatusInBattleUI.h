#pragma once
#include "GameObject.h"
#include "Soul.h"

class StatusInBattleUI : public GameObject
{
protected:
	sf::Text statusText;
	sf::Text hpText;
	sf::RectangleShape hpBar;
	sf::RectangleShape maxhpBar;

	Soul* soul;

	std::string playerName = "Frisk";
	int level = 1;
	int* Hp;
	int* maxHp;

public:
	StatusInBattleUI(const std::string& name = "");
	virtual ~StatusInBattleUI() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;

	void UpdateHpUI();

	void Draw(sf::RenderWindow& window) override;
};

