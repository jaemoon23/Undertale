#pragma once
#include "GameObject.h"

class PlayerInfoUi : public GameObject
{
protected:
	struct PlayerInformation
	{
		std::wstring name;
		int att;
		int def;
		int hp;
		int level;
		int gold;
	};

	PlayerInformation info;

	sf::Sprite playerInfo;

	sf::RectangleShape line;
	sf::Font font;
	std::string fonttexIds = "fonts/DungGeunMo.ttf";

	sf::Text name;
	sf::Text att;
	sf::Text def;
	sf::Text hp;
	sf::Text gold;
	sf::Text exp;
	sf::Text level;


	bool isActive = true;

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

	void SetPlayerName(const std::wstring& playerName);
	void SetPlayerAttack(const std::wstring& playerAtt);
	void SetPlayerDefence(const std::wstring& playerDef);
	void SetPlayerHp(const std::wstring& playerHp);
	void SetPlayerLevel(const std::wstring& playerLevel);
	void SetPlayerGold(const std::wstring& playergold);
};

