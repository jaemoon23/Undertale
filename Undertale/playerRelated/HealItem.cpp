#include "stdafx.h"
#include "HealItem.h"

HealItem::HealItem(const std::string& name, int healAmount)
	: GameObject(name), healAmount(healAmount)
{
}
void HealItem::Init()
{
	healAmount = 5;
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