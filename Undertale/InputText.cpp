#include "stdafx.h"
#include "InputText.h"

InputText::InputText(const std::string name)
{
}

void InputText::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	box.setPosition(pos);
}

void InputText::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	box.setRotation(rot);
}

void InputText::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	box.setScale(s);
}

void InputText::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	box.setOrigin(o);
}

void InputText::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(box, preset);
	}
}
void InputText::SetColor(const sf::Color& color1, const sf::Color& color2)
{
	box.setFillColor(color1);
	box.setOutlineColor(color2);
	text.setFillColor(sf::Color::Black);
}
void InputText::SetSize(const sf::Vector2f& size)
{
	box.setSize(size);
	text.setCharacterSize(box.getSize().x * 0.5f);
}

void InputText::Activate(std::function<void(int)> callback)
{
	active = true;
	currentInput.clear();
	onSubmit = callback;
}

void InputText::Deactivate()
{
	active = false;
	currentInput.clear();
}

void InputText::Init()
{
}

void InputText::Release()
{
}

void InputText::Reset()
{
	text.setScale(box.getScale());
	text.setOrigin({ box.getLocalBounds().width, box.getLocalBounds().height });
	text.setPosition(box.getPosition().x, box.getPosition().y);
}

void InputText::Update(float dt)
{
	
	if (active)
	{
		while (FRAMEWORK.GetWindow().pollEvent(event))
		{
			if (event.type == sf::Event::TextEntered)
			{
				std::cout << event.text.unicode << std::endl;
				if (event.text.unicode >= '0' && event.text.unicode <= '9')
				{
					currentInput += static_cast<char>(event.text.unicode);
					std::cout << currentInput << std::endl;
				}
				else if (event.text.unicode == '\b' && !currentInput.empty())
				{
					currentInput.pop_back();
				}
				else if (event.text.unicode == 13) // ฟฃลอ
				{
					if (!currentInput.empty())
					{
						int value = std::stoi(currentInput);
						onSubmit(value);
						std::cout << value << std::endl;
					}
					Deactivate();
				}
				else if (event.text.unicode == 27) // esc
				{
					Deactivate();
				}
			}
		}
	}
	text.setString(currentInput);
}

void InputText::Draw(sf::RenderWindow& window)
{
	window.draw(box);
	window.draw(text);
}
