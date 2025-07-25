#pragma once
#include "GameObject.h"

class Soul;

class BattleButton : public GameObject
{
protected:
	sf::Sprite sprite;

	std::string offTexId;
	std::string onTexId;

	Soul* soul;

public:
	BattleButton(const std::string& name = "");
	virtual ~BattleButton() = default;

	void SetTexIds(std::string offId, std::string onId) { offTexId = offId; onTexId = onId; }

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void UpdateTexture();

	void Draw(sf::RenderWindow& window) override;
};

