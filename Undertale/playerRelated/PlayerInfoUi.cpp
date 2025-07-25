#include "stdafx.h"
#include "PlayerInfoUi.h"


PlayerInfoUi::PlayerInfoUi(const std::string& name)
	: GameObject(name)
{
}

void PlayerInfoUi::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	playerInfo.setPosition(pos);
}

void PlayerInfoUi::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	playerInfo.setRotation(rot);
}

void PlayerInfoUi::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	playerInfo.setScale(s);
}

void PlayerInfoUi::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	playerInfo.setOrigin(o);
}

void PlayerInfoUi::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(playerInfo, preset);
	}
}

void PlayerInfoUi::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 1;
	SetActive(false);
}

void PlayerInfoUi::Release()
{
}

void PlayerInfoUi::Reset()
{
	font.loadFromFile(fonttexIds);

	playerInfo.setTexture(TEXTURE_MGR.Get("Sprites/backgroundui.png"));
	playerInfo.setPosition(350.f, 100.f);
	playerInfo.setScale(0.4f, 0.6f);

	line.setSize({ 251.f, 285.f });
	line.setPosition(350.f, 103.f);
	line.setFillColor(sf::Color::Transparent);
	line.setOutlineColor(sf::Color::White);
	line.setOutlineThickness(5.f);

	name.setFont(font);
	name.setCharacterSize(20);
	name.setFillColor(sf::Color::White);
	name.setPosition(390.f, 113.f);
	name.setString(info.name);

	level.setFont(font);
	level.setCharacterSize(18);
	level.setFillColor(sf::Color::White);
	level.setPosition(390.f, 147.f);
	level.setString(L"LEVEL : " + std::to_wstring(info.level));

	att.setFont(font);
	att.setCharacterSize(18);
	att.setFillColor(sf::Color::White);
	att.setPosition(390.f, 180.f);
	att.setString(L"ATK : " + std::to_wstring(info.att));

	def.setFont(font);
	def.setCharacterSize(18);
	def.setFillColor(sf::Color::White);
	def.setPosition(390.f, 210.f);
	def.setString(L"DEF : " + std::to_wstring(info.def));

	hp.setFont(font);
	hp.setCharacterSize(18);
	hp.setFillColor(sf::Color::White);
	hp.setPosition(390.f, 240.f);
	hp.setString(L"HP : " + std::to_wstring(info.hp));

	gold.setFont(font);
	gold.setCharacterSize(18);
	gold.setFillColor(sf::Color::White);
	gold.setPosition(390.f, 300.f);
	gold.setString(L"GOLD : " + std::to_wstring(info.gold));

}

void PlayerInfoUi::Update(float dt)
{
}

void PlayerInfoUi::Draw(sf::RenderWindow& window)
{
	if (isActive)
	{
		window.draw(playerInfo);
		window.draw(line);
		window.draw(name);
		window.draw(att);
		window.draw(def);
		window.draw(hp);
		window.draw(level);
		window.draw(gold);
	}
}

void PlayerInfoUi::SetPlayerName(const std::wstring& playerName)
{
	info.name = playerName;
	name.setString(playerName);
}

void PlayerInfoUi::SetPlayerAttack(const std::wstring& playerAtt)
{
	info.att = std::stoi(playerAtt);
	att.setString(L"ATK : " + playerAtt);
}

void PlayerInfoUi::SetPlayerDefence(const std::wstring& playerDef)
{
	info.def = std::stoi(playerDef); // (std::stoi = string to int)
	def.setString(L"DEF : " + playerDef);
}

void PlayerInfoUi::SetPlayerHp(const std::wstring& playerHp)
{
	info.hp = std::stoi(playerHp);
	hp.setString(L"HP : " + playerHp);
}

void PlayerInfoUi::SetPlayerLevel(const std::wstring& playerLevel)
{
	info.level = std::stoi(playerLevel);
	level.setString(L"LEVEL : " + playerLevel);
}

void PlayerInfoUi::SetPlayerGold(const std::wstring& playergold)
{
	info.gold = std::stoi(playergold);
	gold.setString(L"GOLD : " + playergold);
}

