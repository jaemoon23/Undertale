#include "stdafx.h"
#include "TalkObject.h"

TalkObject::TalkObject(const std::string& name)
	: GameObject(name)
{
}

void TalkObject::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	sprite.setPosition(pos);
}

void TalkObject::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	sprite.setRotation(rot);
}

void TalkObject::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	sprite.setScale(s);
}

void TalkObject::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	sprite.setOrigin(o);
}

void TalkObject::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(sprite, preset);
	}
}

void TalkObject::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
}

void TalkObject::Release()
{
}

void TalkObject::Reset()
{
	sprite.setTexture(TEXTURE_MGR.Get(texId), true);
	SetOrigin(Origins::MC);

	player = ((Player*)SCENE_MGR.GetCurrentScene()->FindGameObject("Sprites/idle.png"));
	textWindow = ((TextWindow*)SCENE_MGR.GetCurrentScene()->FindGameObject("textWindow"));

	lineIndex = 0;
	lineCount = lines.size();

	typeTimer = 0.f;
	isDrawingText = false;
}

void TalkObject::Update(float dt)
{
	if (player->GetGlobalBounds().intersects(sprite.getGlobalBounds()))
	{		
		if (InputMgr::GetKeyDown(sf::Keyboard::Z))
		{
			if (lineIndex == lineCount)
			{
				if (name == "savepoint")
				{
					PlayerInfo::Heal(PlayerInfo::maxHp);
					SOUND_MGR.PlaySfx("sounds/snd_heal_c.wav");
				}
				player->SetMove(true);
				textWindow->isDraw = false;
				lineIndex = 0;
			}
			else
			{
				player->SetMove(false);
				textWindow->isDraw = true;
				isDrawingText = true;
				tempLine = lines[lineIndex++];
				charIndex = 0;
			}
		}

		if (isDrawingText)
		{
			typeTimer += dt;
			if (charIndex < tempLine.size() && typeTimer > typeTime)
			{
				typeTimer = 0.f;
				charIndex++;
				currentLine = tempLine.substr(0, charIndex);
				textWindow->line = currentLine;
				textWindow->UpdateText();

				if (tempLine[charIndex - 1] != L' ')
					SOUND_MGR.PlaySfx("sounds/SND_TXT1.wav");
			}
		}
	}
}

void TalkObject::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}