#include "stdafx.h"
#include "dialogueBox.h"

dialogueBox::dialogueBox(const std::string& name)
	: GameObject(name)
{
}

void dialogueBox::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	sprite.setPosition(pos);
	text.setPosition(pos + sf::Vector2f({37.f,3.f}));
}

void dialogueBox::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	sprite.setRotation(rot);
	text.setRotation(rot);
}

void dialogueBox::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	sprite.setScale(s);
	text.setScale(s);
}

void dialogueBox::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	sprite.setOrigin(o);
	text.setOrigin(o);
}

void dialogueBox::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(sprite, preset);
		Utils::SetOrigin(text, preset);
	}
}

void dialogueBox::Init()
{
	text.setCharacterSize(25.f);
	text.setFillColor(sf::Color::Black);
}

void dialogueBox::Release()
{
}

void dialogueBox::Reset()
{
	text.setFont(FONT_MGR.Get("fonts/DungGeunMo.ttf"));
	sprite.setTexture(TEXTURE_MGR.Get("graphics/spr_dialogueBox.png"));
	SetPosition({ size.x * 0.55f, size.y * 0.3f });
}

void dialogueBox::Update(float dt)
{
}

void dialogueBox::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
	window.draw(text);
}