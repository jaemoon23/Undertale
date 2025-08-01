#include "stdafx.h"
#include "TextWindow.h"

TextWindow::TextWindow(const std::string& name)
	: GameObject(name)
{
}

void TextWindow::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	sprite.setPosition(pos);
}

void TextWindow::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	sprite.setRotation(rot);
}

void TextWindow::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	sprite.setScale(s);
}

void TextWindow::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	sprite.setOrigin(o);
}

void TextWindow::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(sprite, preset);
	}
}

void TextWindow::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;
	sprite.setPosition({ 320.f, 395.f });
}

void TextWindow::Release()
{
}

void TextWindow::Reset()
{
	sprite.setTexture(TEXTURE_MGR.Get("graphics/TextWindow.png"));
	SetOrigin(Origins::MC);

	isDraw = false;
}

void TextWindow::Update(float dt)
{
}

void TextWindow::Draw(sf::RenderWindow& window)
{
	if(isDraw)
		window.draw(sprite);
}