#include "stdafx.h"
#include "BattleDialogueBox.h"
#include "SceneBattle.h"

BattleDialogueBox::BattleDialogueBox(const std::string& name)
	: GameObject(name)
{
}

void BattleDialogueBox::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	sprite.setPosition(pos);
	text.setPosition(pos + sf::Vector2f({ 37.f,3.f }));
}

void BattleDialogueBox::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	sprite.setRotation(rot);
	text.setRotation(rot);
}

void BattleDialogueBox::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	sprite.setScale(s);
	text.setScale(s);
}

void BattleDialogueBox::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	sprite.setOrigin(o);
	text.setOrigin(o);
}

void BattleDialogueBox::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(sprite, preset);
		Utils::SetOrigin(text, preset);
	}
}

void BattleDialogueBox::Init()
{
	text.setCharacterSize(25.f);
	text.setFillColor(sf::Color::Black);
}

void BattleDialogueBox::Release()
{
}

void BattleDialogueBox::Reset()
{
	scene = ((SceneBattle*)SCENE_MGR.GetCurrentScene());

	text.setFont(FONT_MGR.Get("fonts/DungGeunMo.ttf"));
	sprite.setTexture(TEXTURE_MGR.Get("graphics/spr_dialogueBox.png"));
	SetPosition({ size.x * 0.55f, size.y * 0.3f });
}

void BattleDialogueBox::Update(float dt)
{
}

void BattleDialogueBox::Draw(sf::RenderWindow& window)
{
	if (isDraw)
	{
		window.draw(sprite);
		window.draw(text);
	}
}