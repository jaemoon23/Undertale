#include "stdafx.h"
#include "DialogueBox.h"
#include "Player.h"


DialogueBox::DialogueBox(const std::string& name)
	: GameObject(name)
{
}

void DialogueBox::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	dialogueBox.setPosition(pos);
}

void DialogueBox::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	dialogueBox.setRotation(rot);
}

void DialogueBox::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	dialogueBox.setScale(s);
}

void DialogueBox::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	dialogueBox.setOrigin(o);
}

void DialogueBox::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(dialogueBox, preset);
	}
}

void DialogueBox::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 1;
}

void DialogueBox::Release()
{
}

void DialogueBox::Reset()
{
	dialogueBox.setTexture(TEXTURE_MGR.Get(dialogueboxtexIds));
	dialogueBox.setPosition(320.f, 400.f);
	dialogueBox.setScale(0.8f, 0.23f);
	SetOrigin(Origins::MC);

	line.setSize({ 504.f,101.f });
	line.setFillColor(sf::Color::Transparent);
	line.setOutlineColor(sf::Color::White);
	line.setPosition({dialogueBox.getPosition().x - 252.f, dialogueBox.getPosition().y - 51.f});
	line.setOutlineThickness(5.f);

	SetActive(false);
}

void DialogueBox::Update(float dt)
{
	//if (InputMgr::GetKeyDown(sf::Keyboard::Z))
	//{
	//	isActive = true;	
	//}
}

void DialogueBox::Draw(sf::RenderWindow& window)
{
		window.draw(dialogueBox);
		window.draw(line);
}