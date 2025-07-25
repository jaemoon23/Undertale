#include "stdafx.h"
#include "Soul.h"
#include "SceneBattle.h"

Soul::Soul(const std::string& name)
	: GameObject(name)
{
}

void Soul::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	sprite.setPosition(pos);
}

void Soul::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	sprite.setRotation(rot);
}

void Soul::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	sprite.setScale(s);
}

void Soul::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	sprite.setOrigin(o);
}

void Soul::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(sprite, preset);
	}
}

void Soul::Init()
{
	SetOrigin(Origins::MC);
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
	SetPosition({ size.x * 0.03f, size.y * 0.93f });
}

void Soul::Release()
{
}

void Soul::Reset()
{
	SetPosition({ size.x * 0.03f, size.y * 0.93f });

	originColor = sprite.getColor();
	originColor.a = 255;
	blinkColor = sprite.getColor();
	blinkColor.a = 100;

	scene = (SceneBattle*)SCENE_MGR.GetCurrentScene();
	btIndex = &(scene->btIndex);
	actChooseIndex = &(scene->actChooseIndex);
	actChooseCount = &(scene->actChooseCount);
	itemChooseIndex = &(scene->itemChooseIndex);
	itemChooseCount = &(scene->itemChooseCount);
	mercyChooseIndex = &(scene->mercyChooseIndex);
	sprite.setTexture(TEXTURE_MGR.Get("graphics/spr_heart_battle_pl_0.png"));
}

void Soul::Update(float dt)
{
	hitBox.UpdateTransform(sprite, sprite.getLocalBounds());

	sf::Vector2f pos = GetPosition();
	if (scene->isMyTurn)
	{
		switch (scene->btState)
		{
		case ButtonState::None:
			if (*btIndex != 0 && InputMgr::GetKeyDown(sf::Keyboard::Left))
			{
				pos.x -= size.x * 0.26f;
				SetPosition(pos);
				(*btIndex)--;
			}
			if (*btIndex != 3 && InputMgr::GetKeyDown(sf::Keyboard::Right))
			{
				pos.x += size.x * 0.26f;
				SetPosition(pos);
				(*btIndex)++;
			}
			break;
		case ButtonState::ChooseFight:
			if (InputMgr::GetKeyDown(sf::Keyboard::Z))
			{
				scene->btState = ButtonState::Fight;
			}
			else if (InputMgr::GetKeyDown(sf::Keyboard::X))
			{
				scene->btState = ButtonState::None;
				SetPosition({ size.x * 0.03f + size.x * 0.26f * scene->btIndex, size.y * 0.93f });
			}
			break;
		case ButtonState::ChooseAct:
			if (*actChooseIndex != 0 && *actChooseIndex != 2 && InputMgr::GetKeyDown(sf::Keyboard::Left))
			{
				(*actChooseIndex)--; 
				SetPosition({ size.x * 0.05f + size.x * 0.5f * (*actChooseIndex % 2), size.y * 0.57f + size.y * 0.09f * ((*actChooseIndex) / 2)});
			}
			if (*actChooseIndex != 1 && *actChooseIndex != 3 && InputMgr::GetKeyDown(sf::Keyboard::Right))
			{
				*actChooseIndex = Utils::ClampInt(*actChooseIndex + 1, 0, *actChooseCount - 1);
				SetPosition({ size.x * 0.05f + size.x * 0.5f * (*actChooseIndex % 2), size.y * 0.57f + size.y * 0.09f * ((*actChooseIndex) / 2) });
			}
			if (*actChooseIndex != 0 && *actChooseIndex != 1 && InputMgr::GetKeyDown(sf::Keyboard::Up))
			{
				*actChooseIndex -= 2;
				SetPosition({ size.x * 0.05f + size.x * 0.5f * (*actChooseIndex % 2), size.y * 0.57f + size.y * 0.09f * ((*actChooseIndex) / 2) });
			}
			if (*actChooseIndex != 2 && *actChooseIndex != 3 && InputMgr::GetKeyDown(sf::Keyboard::Down))
			{
				*actChooseIndex = Utils::ClampInt(*actChooseIndex + 2, 0, *actChooseCount - 1);
				SetPosition({ size.x * 0.05f + size.x * 0.5f * (*actChooseIndex % 2), size.y * 0.57f + size.y * 0.09f * ((*actChooseIndex) / 2) });
			}

			if (InputMgr::GetKeyDown(sf::Keyboard::Z))
			{
				scene->btState = ButtonState::Act;
				scene->SetActDescribe();
			}
			else if (InputMgr::GetKeyDown(sf::Keyboard::X))
			{
				scene->btState = ButtonState::None;
				SetPosition({ size.x * 0.03f + size.x * 0.26f * scene->btIndex, size.y * 0.93f });
			}
			break;
		case ButtonState::ChooseItem:
			if (*itemChooseIndex != 0 && *itemChooseIndex != 2 && InputMgr::GetKeyDown(sf::Keyboard::Left))
			{
				(*itemChooseIndex)--;
				SetPosition({ size.x * 0.05f + size.x * 0.5f * (*itemChooseIndex % 2), size.y * 0.57f + size.y * 0.09f * ((*itemChooseIndex) / 2) });
			}
			if (*itemChooseIndex != 1 && *itemChooseIndex != 3 && InputMgr::GetKeyDown(sf::Keyboard::Right))
			{
				*itemChooseIndex = Utils::ClampInt(*itemChooseIndex + 1, 0, *itemChooseCount - 1);
				SetPosition({ size.x * 0.05f + size.x * 0.5f * (*itemChooseIndex % 2), size.y * 0.57f + size.y * 0.09f * ((*itemChooseIndex) / 2) });
			}
			if (*itemChooseIndex != 0 && *itemChooseIndex != 1 && InputMgr::GetKeyDown(sf::Keyboard::Up))
			{
				*itemChooseIndex -= 2;
				SetPosition({ size.x * 0.05f + size.x * 0.5f * (*itemChooseIndex % 2), size.y * 0.57f + size.y * 0.09f * ((*itemChooseIndex) / 2) });
			}
			if (*itemChooseIndex != 2 && *itemChooseIndex != 3 && InputMgr::GetKeyDown(sf::Keyboard::Down))
			{
				*itemChooseIndex = Utils::ClampInt(*itemChooseIndex + 2, 0, *itemChooseCount - 1);
				SetPosition({ size.x * 0.05f + size.x * 0.5f * (*itemChooseIndex % 2), size.y * 0.57f + size.y * 0.09f * ((*itemChooseIndex) / 2) });
			}

			if (InputMgr::GetKeyDown(sf::Keyboard::Z))
			{
				scene->TryUseItem();
			}
			else if (InputMgr::GetKeyDown(sf::Keyboard::X))
			{
				scene->btState = ButtonState::None;
				SetPosition({ size.x * 0.03f + size.x * 0.26f * scene->btIndex, size.y * 0.93f });
			}
			break;
		case ButtonState::ChooseMercy:
			if (*mercyChooseIndex == 0 && InputMgr::GetKeyDown(sf::Keyboard::Down))
			{
				(*mercyChooseIndex)++;
				SetPosition({ size.x * 0.05f, size.y * 0.57f + size.y * 0.09f * (*mercyChooseIndex) });
			}
			if (*mercyChooseIndex == 1 && InputMgr::GetKeyDown(sf::Keyboard::Up))
			{
				(*mercyChooseIndex)--;
				SetPosition({ size.x * 0.05f, size.y * 0.57f + size.y * 0.09f * (*mercyChooseIndex) });
			}

			if (InputMgr::GetKeyDown(sf::Keyboard::Z))
			{
				scene->TryMercy();
			}
			else if (InputMgr::GetKeyDown(sf::Keyboard::X))
			{
				scene->btState = ButtonState::None;
				SetPosition({ size.x * 0.03f + size.x * 0.26f * scene->btIndex, size.y * 0.93f });
			}
			break;
		case ButtonState::Fight:
			break;
		case ButtonState::Act:
			break;
		case ButtonState::Item:
			break;
		case ButtonState::Mercy:
			break;
		}
	}
	else
	{
		pos.x += InputMgr::GetAxis(Axis::Horizontal) * moveSpeed * dt;
		pos.y += InputMgr::GetAxis(Axis::Vertical) * moveSpeed * dt;
		pos.x = Utils::Clamp(pos.x, minX, maxX);
		pos.y = Utils::Clamp(pos.y, minY, maxY);
		SetPosition(pos);
	}

	if(isBlink)
		BlinkUpdate(dt);
}

void Soul::Draw(sf::RenderWindow& window)
{
	if(scene->btState != ButtonState::Fight && scene->btState != ButtonState::Act)
		window.draw(sprite);
	hitBox.Draw(window);
}

void Soul::SetBoundary(sf::FloatRect bounds)
{
	sf::FloatRect soulBound = sprite.getGlobalBounds();
	minX = bounds.left + soulBound.width * 0.5f;
	minY = bounds.top + soulBound.height * 0.5f;
	maxX = bounds.left + bounds.width - soulBound.width - 5.f;
	maxY = bounds.top + bounds.height - soulBound.height - 5.f;
}

void Soul::TakeDamage(int damage)
{
	hp -= damage;
	if (hp <= 0)
	{
		hp = 0;
		scene->PlayerDie();
	}
}

void Soul::BlinkUpdate(float dt)
{
	blinkTimer += dt;
	blinkPeriodTimer += dt;
	if (blinkTimer >= blinkTime)
	{
		isBlink = false;
		blinkTimer = 0.f;
		blinkPeriodTimer = 0.f;
		sprite.setColor(originColor);
	}

	if (blinkPeriodTimer >= blinkPeriod)
	{
		if (sprite.getColor() == originColor)
			sprite.setColor(blinkColor);
		else
			sprite.setColor(originColor);
		blinkPeriodTimer = 0.f;
	}
}
