#include "stdafx.h"
#include "StatusInBattleUI.h"

StatusInBattleUI::StatusInBattleUI(const std::string& name)
	: GameObject(name)
{
}

void StatusInBattleUI::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	statusText.setPosition(pos);
	hpBar.setPosition(pos + sf::Vector2f(265.f, 8.f));
	sf::FloatRect hpbarRect = hpBar.getGlobalBounds();
	hpText.setPosition({hpbarRect.left + hpbarRect.width + 55.f, hpbarRect.top - 8.f});
}

void StatusInBattleUI::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	statusText.setRotation(rot);
	hpText.setRotation(rot);
	hpBar.setRotation(rot);
}

void StatusInBattleUI::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	statusText.setScale(s);
	hpText.setScale(s);
	hpBar.setScale(s);
}

void StatusInBattleUI::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	statusText.setOrigin(o);
	hpText.setOrigin(o);
	hpBar.setOrigin(o);
}

void StatusInBattleUI::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(statusText, preset);
		Utils::SetOrigin(hpText, preset);
		Utils::SetOrigin(hpBar, preset);
	}
}

void StatusInBattleUI::Init()
{
	statusText.setFont(FONT_MGR.Get("fonts/DungGeunMo.ttf"));
	statusText.setString(playerName + "   LV" + std::to_string(level) + "    HP");
	statusText.setCharacterSize(30.f);

	hpText.setFont(FONT_MGR.Get("fonts/DungGeunMo.ttf"));
	hpText.setString(std::to_string(playerCurrentHp) + "/" + std::to_string(playerMaxHp));
	hpText.setCharacterSize(30.f);

	hpBar.setFillColor(sf::Color::Yellow);
	hpBar.setSize({ 2.f * playerMaxHp, 30.f });
}

void StatusInBattleUI::Release()
{
}

void StatusInBattleUI::Reset()
{
}

void StatusInBattleUI::Update(float dt)
{
}

void StatusInBattleUI::Draw(sf::RenderWindow& window)
{
	window.draw(statusText);
	window.draw(hpText);
	window.draw(hpBar);
}