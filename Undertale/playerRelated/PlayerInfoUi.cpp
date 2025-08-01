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
	sortingOrder = 2;
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
	name.setString("Frisk");

	level.setFont(font);
	level.setCharacterSize(18);
	level.setFillColor(sf::Color::White);
	level.setPosition(390.f, 157.f);
	level.setString(L"LV " + std::to_wstring(PlayerInfo::lv));

	hp.setFont(font);
	hp.setCharacterSize(18);
	hp.setFillColor(sf::Color::White);
	hp.setPosition(390.f, 200.f);
	hp.setString(L"HP " + std::to_wstring(PlayerInfo::hp)+ L" / "+std::to_wstring(PlayerInfo::maxHp));

	att.setFont(font);
	att.setCharacterSize(18);
	att.setFillColor(sf::Color::White);
	att.setPosition(390.f, 243.f);
	att.setString(L"AT : " + std::to_wstring(PlayerInfo::ATK));

	exp.setFont(font);
	exp.setCharacterSize(18);
	exp.setFillColor(sf::Color::White);
	exp.setPosition(390.f, 286.f);
	exp.setString(L"EXP : " + std::to_wstring(PlayerInfo::exp));

	gold.setFont(font);
	gold.setCharacterSize(18);
	gold.setFillColor(sf::Color::White);
	gold.setPosition(390.f, 329.f);
	gold.setString(L"GOLD : " + std::to_wstring(PlayerInfo::gold));

}

void PlayerInfoUi::Update(float dt)
{
	level.setString(L"LV " + std::to_wstring(PlayerInfo::lv));
	hp.setString(L"HP : " + std::to_wstring(PlayerInfo::hp) + L" / " + std::to_wstring(PlayerInfo::maxHp));
	att.setString(L"AT : " + std::to_wstring(PlayerInfo::ATK));
	exp.setString(L"EXP : " + std::to_wstring(PlayerInfo::exp));
	gold.setString(L"GOLD : " + std::to_wstring(PlayerInfo::gold));
}

void PlayerInfoUi::Draw(sf::RenderWindow& window)
{
	if (GetActive()) 
	{
		window.draw(playerInfo);
		window.draw(line);
		window.draw(name);
		window.draw(att);
		window.draw(hp);
		window.draw(level);
		window.draw(gold);
		window.draw(exp);
	}
}

