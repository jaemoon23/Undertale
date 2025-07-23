#include "stdafx.h"
#include "Button.h"

Button::Button(const std::string& name) : GameObject(name)
{
	
}

void Button::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Button::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void Button::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Button::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Button::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}
void Button::SetColor(const sf::Color& color1, const sf::Color& color2)
{
	body.setFillColor(color1);
	body.setOutlineColor(color2);
	body.setOutlineThickness(1.f);
}
void Button::SetSize(const sf::Vector2f& size)
{
	body.setSize(size);
}
void Button::setCallback(std::function<void()> func)
{
	onClick = func;
}
void Button::Init()
{
}

void Button::Release()
{
}

void Button::Reset()
{
	
	body.setFillColor(sf::Color::White);
	text.setOrigin(body.getLocalBounds().width * 0.5f, body.getLocalBounds().height * 0.5f);
}

void Button::Update(float dt)
{
	// 마우스 포지션 가져오기
	bounds = body.getGlobalBounds();
	sf::Vector2i pixelPos = sf::Mouse::getPosition(FRAMEWORK.GetWindow());
	sf::Vector2f worldPos = FRAMEWORK.GetWindow().mapPixelToCoords(pixelPos);

	text.setPosition(body.getPosition().x, body.getPosition().y);

	if (bounds.contains(worldPos))
	{
		//std::cout << "올라감" << std::endl;
		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
		{
			onClick();
		}
	}
}

void Button::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}


