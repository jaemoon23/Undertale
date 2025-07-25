#include "stdafx.h"
#include "TestBackGround.h"

TestBackGround::TestBackGround(const std::string& name)
	: GameObject(name)
{
}

void TestBackGround::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	testbackground.setPosition(pos);
}

void TestBackGround::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	testbackground.setRotation(rot);
}

void TestBackGround::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	testbackground.setScale(s);
}

void TestBackGround::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	testbackground.setOrigin(o);
}

void TestBackGround::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(testbackground, preset);
	}
}

void TestBackGround::Init()
{
	sortingLayer = SortingLayers::Background;
	sortingOrder = 0;
}

void TestBackGround::Release()
{
}

void TestBackGround::Reset()
{
	sortingLayer = SortingLayers::Background;
	sortingOrder = 0;
	testbackground.setTexture(TEXTURE_MGR.Get(testtexIds));
	testbackground.setPosition(0.f, 0.f);
	testbackground.setScale(2.f, 2.f);
	SetOrigin(Origins::MC);
}

void TestBackGround::Update(float dt)
{
}

void TestBackGround::Draw(sf::RenderWindow& window)
{
	window.draw(testbackground);
}