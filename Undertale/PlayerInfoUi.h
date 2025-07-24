#pragma once
#include "GameObject.h"

class PlayerInfoUi : public GameObject
{
protected:
	struct PlayerInfo
	{
		std::wstring name;
		//int hp;
	};

	PlayerInfo info;

	sf::Sprite playerInfo;
	std::string playerInfotexIds = "Sprites/backgroundui.png";

	sf::RectangleShape line;
	sf::Font font;
	std::string fonttexIds = "fonts/DungGeunMo.ttf";

	sf::Text name;
	sf::Text att;
	sf::Text def;
	sf::Text gold;
	sf::Text exp;

public:
	PlayerInfoUi(const std::string& name = "");
	virtual ~PlayerInfoUi() = default;

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

