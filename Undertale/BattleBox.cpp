#include "stdafx.h"
#include "BattleBox.h"
#include "SceneBattle.h"
#include "Soul.h"

BattleBox::BattleBox(const std::string& name)
	: GameObject(name)
{
}

void BattleBox::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	box.setPosition(pos);
	fightSprite.setPosition(pos + sf::Vector2f({0.f,-3.f}));
	fightLine.setPosition(pos + sf::Vector2f({ -pos.x,-3.f }));
	startDescribe.setPosition(pos + sf::Vector2f({ -size.x * 0.51f + 35.f,-60.f }));
	fightAniSprite.setPosition(pos + sf::Vector2f({ -30.f,-240.f }));
}

void BattleBox::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	box.setRotation(rot);
}

void BattleBox::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	box.setScale(s);
}

void BattleBox::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	box.setOrigin(o);
}

void BattleBox::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(box, preset);
		Utils::SetOrigin(fightSprite, preset);
		Utils::SetOrigin(fightLine, preset);
	}
}

void BattleBox::Init()
{
	animator.SetTarget(&fightAniSprite);

	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
	box.setFillColor(sf::Color::Black);
	box.setOutlineColor(sf::Color::White);
	box.setOutlineThickness(5.f);

	fightLine.setFillColor(sf::Color::White);
	fightLine.setOutlineColor(sf::Color::White);
	fightLine.setOutlineThickness(0.5f);

	startDescribe.setFont(FONT_MGR.Get("fonts/DungGeunMo.ttf"));
	startDescribe.setCharacterSize(30.f);

	maxHpBar.setFillColor(sf::Color::Yellow);
	maxHpBar.setSize({ size.x * 0.3f, size.y * 0.05f });
	maxHpBar.setPosition({ size.x * 0.3f, size.y * 0.2f });

	hpBar.setFillColor(sf::Color::Green);
	hpBar.setSize({ size.x * 0.3f, size.y * 0.05f });
	hpBar.setPosition({ size.x * 0.3f, size.y * 0.2f });
}

void BattleBox::Release()
{
}

void BattleBox::Reset()
{
	scene = ((SceneBattle*)SCENE_MGR.GetCurrentScene());
	monsterHp = &(scene->monsterHp);
	monsterMaxHp = &(scene->monsterMaxHp);

	fightSprite.setTexture(TEXTURE_MGR.Get("graphics/spr_dumbtarget_0.png"));

	box.setSize({ size.x * 0.95f, size.y * 0.25f });
	fightLine.setSize({ size.x * 0.007f, size.y * 0.23f });
	SetOrigin(Origins::MC);
	SetPosition({ size.x * 0.51f, size.y * 0.67f });

	std::wstring ws = utf8_to_wstring(startStr);
	startDescribe.setString(ws);
}

void BattleBox::Update(float dt)
{
	if (scene->btState == ButtonState::Fight)
	{
		if (!fightBtPress)
		{
			sf::Vector2f pos = fightLine.getPosition();
			pos.x += fightLineSpeed * dt;
			fightLine.setPosition(pos);
		}

		if (InputMgr::GetKeyDown(sf::Keyboard::Z))
		{
			isDrawHpBar = true;
			animator.Play("animations/fist.csv");
			*monsterHp -= 20;
			fightBtPress = true;
			isAttacking = true;
		}

		if (fightBtPress)
		{
			timer += dt;
			if (timer >= fightAniTime)
			{
				timer = 0.f;
				fightBtPress = false;
				isAttacking = false;
				isDrawHpBar = false;
				scene->isMyTurn = false;
				scene->btState = ButtonState::None;
				sf::Vector2f hpBarSize = hpBar.getSize();
				hpBarSize.x *= (((float)*monsterHp) / *monsterMaxHp);
				hpBar.setSize(hpBarSize);
				box.setSize({ size.x * 0.4f, size.y * 0.25f });
				Utils::SetOrigin(box, Origins::MC);				
				scene->SetMonsterTurn();
			}
		}
	}

	animator.Update(dt);
}

void BattleBox::UpdateBox()
{
	switch (scene->btState)
	{
	case ButtonState::None:
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

void BattleBox::Draw(sf::RenderWindow& window)
{
	window.draw(box);
	if (scene->isMyTurn)
	{
		switch (scene->btState)
		{
		case ButtonState::None:
			window.draw(startDescribe);
			break;
		case ButtonState::Fight:
			window.draw(fightSprite);
			window.draw(fightLine);
			break;
		case ButtonState::Act:
			break;
		case ButtonState::Item:
			break;
		case ButtonState::Mercy:
			break;
		}
	}

	if (isAttacking)
	{
		window.draw(fightAniSprite);
	}

	if (isDrawHpBar)
	{
		window.draw(maxHpBar);
		window.draw(hpBar);
	}
}