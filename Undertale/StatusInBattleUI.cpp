#include "stdafx.h"
#include "StatusInBattleUI.h"
#include "SceneBattle.h"

StatusInBattleUI::StatusInBattleUI(const std::string& name)
	: GameObject(name)
{
}

void StatusInBattleUI::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	statusText.setPosition(pos);
	hpBar.setPosition(pos + sf::Vector2f(265.f, 8.f));
	maxhpBar.setPosition(pos + sf::Vector2f(265.f, 8.f));
	sf::FloatRect hpbarRect = hpBar.getGlobalBounds();
	hpText.setPosition({hpbarRect.left + hpbarRect.width + 55.f, hpbarRect.top - 8.f});
}

void StatusInBattleUI::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	statusText.setRotation(rot);
	hpText.setRotation(rot);
	hpBar.setRotation(rot);
	maxhpBar.setRotation(rot);
}

void StatusInBattleUI::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	statusText.setScale(s);
	hpText.setScale(s);
	hpBar.setScale(s);
	maxhpBar.setScale(s);
}

void StatusInBattleUI::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	statusText.setOrigin(o);
	hpText.setOrigin(o);
	hpBar.setOrigin(o);
	maxhpBar.setOrigin(o);
}

void StatusInBattleUI::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(statusText, preset);
		Utils::SetOrigin(hpText, preset);
		Utils::SetOrigin(hpBar, preset);
		Utils::SetOrigin(maxhpBar, preset);
	}
}

void StatusInBattleUI::Init()
{
	statusText.setString(playerName + "   LV" + std::to_string(level) + "    HP");
	statusText.setCharacterSize(30.f);

	hpText.setCharacterSize(30.f);

	hpBar.setFillColor(sf::Color::Yellow);
	maxhpBar.setFillColor(sf::Color::Red);	
}

void StatusInBattleUI::Release()
{
}

void StatusInBattleUI::Reset()
{
	statusText.setFont(FONT_MGR.Get("fonts/DungGeunMo.ttf"));
	hpText.setFont(FONT_MGR.Get("fonts/DungGeunMo.ttf"));
	soul = ((SceneBattle*)SCENE_MGR.GetCurrentScene())->GetSoul();
	Hp = &(soul->hp);
	maxHp = &(soul->maxHp);
	hpText.setString(std::to_string(*Hp) + "/" + std::to_string(*maxHp));
	hpBar.setSize({ 2.f * *Hp, 30.f });
	maxhpBar.setSize({ 2.f * *maxHp, 30.f });
}

void StatusInBattleUI::Update(float dt)
{
}

void StatusInBattleUI::UpdateHpUI()
{
	hpText.setString(std::to_string(*Hp) + "/" + std::to_string(*maxHp));
	hpBar.setSize({ 2.f * *Hp, 30.f });
}

void StatusInBattleUI::Draw(sf::RenderWindow& window)
{
	window.draw(statusText);
	window.draw(hpText);
	window.draw(maxhpBar);
	window.draw(hpBar);
}