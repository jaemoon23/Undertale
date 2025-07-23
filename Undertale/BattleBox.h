#pragma once
#include "GameObject.h"
class BattleBox : public GameObject
{
protected:
	sf::RectangleShape box;

	sf::Text startDescribe;

	sf::Text describe1;
	sf::Text describe2;
	sf::Text describe3;
	sf::Text describe4;

	sf::Vector2f size = { 640.f,480.f };

public:
	std::string startStr;

	BattleBox(const std::string& name = "");
	virtual ~BattleBox() = default;

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
};

