#include "stdafx.h"
#include "HealItem.h"

HealItem::HealItem(const std::string& name)
	: GameObject(name)
{
}


void HealItem::Init()
{
}

void HealItem::Release()
{
}

void HealItem::Reset()
{
}

void HealItem::Update(float dt)
{
}

void HealItem::Draw(sf::RenderWindow& window)
{
}

void HealItem::Use(Player* player)
{
	if (player)
	{
		player->Use(healAmount, player->GetMaxHp());
	}
}
