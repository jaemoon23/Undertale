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

	font.loadFromFile("fonts/DungGeunMo.ttf");
	dialogueText.setFont(font);
	dialogueText.setCharacterSize(24);
	dialogueText.setFillColor(sf::Color::White);
	dialogueText.setPosition({ dialogueBox.getPosition().x - 240.f, dialogueBox.getPosition().y - 40.f });

	SetActive(false);
}

void DialogueBox::Update(float dt)
{
	if (!GetActive()) return;
	{
		UpdateTypingEffect(dt);
		dialogueText.setString(currentText);
	}
}

void DialogueBox::Draw(sf::RenderWindow& window)
{
	if (!GetActive()) return;
	{
		window.draw(dialogueBox);
		window.draw(line);
		window.draw(dialogueText);
	}

}

void DialogueBox::StartDialogue(const std::vector<std::wstring>& lines)
{
	isActive = true;
	dialogueLines = lines;
	currentLineIndex = 0;
	TypingEffect(dialogueLines[currentLineIndex], typingSpeed);

	if (!dialogueLines.empty())
	{
		dialogueText.setString(dialogueLines[currentLineIndex]);  // sf::Text´Â std::wstring Áö¿ø
	}
	SetActive(true);
}

void DialogueBox::NextLine()
{
	if (currentLineIndex + 1 < dialogueLines.size())
	{
		isActive = true;
		currentLineIndex++;
		dialogueText.setString(dialogueLines[currentLineIndex]);
		TypingEffect(dialogueLines[currentLineIndex], typingSpeed);
	}
	else
	{
		isActive = false;
		SetActive(false);
	}
}

void DialogueBox::TypingEffect(const std::wstring& text, float speed)
{
	fullText = text;
	currentText.clear();
	charIndex = 0;
	typingTimer = 0.f;
	typingSpeed = speed;
}

void DialogueBox::UpdateTypingEffect(float dt)
{
	if (charIndex < fullText.size())
	{
		typingTimer += dt;
		if (typingTimer >= typingSpeed)
		{
			typingTimer = 0.f;
			currentText += fullText[charIndex];
			charIndex++;
		}
	}
}

