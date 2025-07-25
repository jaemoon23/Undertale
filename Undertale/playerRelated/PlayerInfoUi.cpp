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

	info.name = L"플레이어";
	name.setFont(font);
	name.setString(info.name);
	name.setCharacterSize(20);
	name.setFillColor(sf::Color::White);
	name.setPosition(390.f, 123.f);

	att.setFont(font);
	att.setCharacterSize(18);
	att.setFillColor(sf::Color::White);
	att.setPosition(390.f, 153.f); 
	att.setString(L"ATK : " + std::to_wstring(info.att));

}

void PlayerInfoUi::Update(float dt)
{
}

void PlayerInfoUi::Draw(sf::RenderWindow& window)
{
	if (isActive)
	{
		window.draw(playerInfo);
		std::cout << playerInfo.getPosition().x << playerInfo.getPosition().y << std::endl;
		window.draw(line);
		window.draw(name);
		window.draw(att);
	}
}

void PlayerInfoUi::SetPlayerName(const std::wstring& playerName)
{
	info.name = playerName;
	name.setString(info.name);
}

void PlayerInfoUi::SetPlayerAttack(const std::wstring& playerAtt)
{
	info.att = std::stoi(playerAtt);
	att.setString(L"ATK : " + playerAtt);
}

