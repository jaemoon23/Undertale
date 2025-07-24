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

	startDescribe.setCharacterSize(30.f);
	describe1.setCharacterSize(30.f);
	describe1.setPosition({ size.x * 0.09f, size.y * 0.54f });
	describe2.setCharacterSize(30.f);
	describe2.setPosition({ size.x * 0.59f, size.y * 0.54f });
	describe3.setCharacterSize(30.f);
	describe3.setPosition({ size.x * 0.09f, size.y * 0.63f });
	describe4.setCharacterSize(30.f);
	describe4.setPosition({ size.x * 0.59f, size.y * 0.63f });

	maxHpBar.setFillColor(sf::Color(128, 128, 128));
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
	hpBar.setSize({ size.x * 0.3f, size.y * 0.05f });
	scene = ((SceneBattle*)SCENE_MGR.GetCurrentScene());
	monsterHp = &(scene->monsterHp);
	monsterMaxHp = &(scene->monsterMaxHp);

	fightSprite.setTexture(TEXTURE_MGR.Get("graphics/spr_dumbtarget_0.png"));

	box.setSize({ size.x * 0.95f, size.y * 0.25f });
	fightLine.setSize({ size.x * 0.007f, size.y * 0.23f });
	SetOrigin(Origins::MC);
	SetPosition({ size.x * 0.51f, size.y * 0.67f });

	startDescribe.setFont(FONT_MGR.Get("fonts/DungGeunMo.ttf"));
	describe1.setFont(FONT_MGR.Get("fonts/DungGeunMo.ttf"));
	describe2.setFont(FONT_MGR.Get("fonts/DungGeunMo.ttf"));
	describe3.setFont(FONT_MGR.Get("fonts/DungGeunMo.ttf"));
	describe4.setFont(FONT_MGR.Get("fonts/DungGeunMo.ttf"));
}

void BattleBox::Update(float dt)
{
	if (scene->btState == ButtonState::Fight)
	{
		if (!fightBtPress && !isHpAni)
		{
			sf::Vector2f pos = fightLine.getPosition();
			pos.x += fightLineSpeed * dt;
			fightLine.setPosition(pos);
		}

		if (InputMgr::GetKeyDown(sf::Keyboard::Z))
		{
			isDrawHpBar = true;
			animator.Play("animations/fist.csv");
			*monsterHp -= scene->playerATK;
			fightBtPress = true;
			isAttacking = true;
			scene->isMonsterBlink = true;
		}

		if (fightBtPress)
		{
			timer += dt;
			if (timer >= fightAniTime)
			{
				timer = 0.f;
				isHpAni = true;
				fightBtPress = false;
				isAttacking = false;
				minusHpbarSize = maxHpBar.getSize().x * (((float)scene->playerATK) / *monsterMaxHp);
			}
		}

		if (isHpAni)
		{
			timer += dt;
			sf::Vector2f hpBarSize = hpBar.getSize();
			hpBarSize.x -= minusHpbarSize * dt / hpAniTime;
			hpBar.setSize(hpBarSize);
			if (hpBarSize.x <= 0)
			{
				hpBarSize.x = 0;
				hpBar.setSize(hpBarSize);
				timer = 0.f;
				isHpAni = false;
				isDrawHpBar = false;
				scene->MonsterDie();
			}
			else if (timer >= hpAniTime)
			{
				sf::Vector2f hpBarSize = maxHpBar.getSize();
				hpBarSize.x *= (((float)*monsterHp) / *monsterMaxHp);
				hpBar.setSize(hpBarSize);
				timer = 0.f;
				isHpAni = false;
				isDrawHpBar = false;
				scene->SetMonsterTurn();
			}
		}
	}
	else if (scene->btState == ButtonState::Act)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::Z))
		{
			scene->SetMonsterTurn();
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
	case ButtonState::ChooseFight:
		describe1.setFillColor(sf::Color::White);
		describe1.setString(describeStr[0]);
		break;
	case ButtonState::ChooseAct:
		describe1.setFillColor(sf::Color::White);
		describe1.setString(describeStr[0]);
		describe2.setString(describeStr[1]);
		describe3.setString(describeStr[2]);
		describe4.setString(describeStr[3]);
		break;
	case ButtonState::ChooseItem:
		describe1.setFillColor(sf::Color::White);
		describe1.setString(describeStr[0]);
		describe2.setString(describeStr[1]);
		describe3.setString(describeStr[2]);
		describe4.setString(describeStr[3]);
		break;
	case ButtonState::ChooseMercy:
		if (scene->mercyPoint >= scene->mercyCanPoint)
		{
			describe1.setFillColor(sf::Color::Yellow);
		}
		else
		{
			describe1.setFillColor(sf::Color::White);
		}
		describe1.setString(describeStr[0]);
		describe3.setString(describeStr[2]);
		break;
	case ButtonState::Fight:
		break;
	case ButtonState::Act:
		describe1.setString(describeStr[0]);
		describe3.setString(describeStr[2]);
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
		case ButtonState::ChooseFight:
			window.draw(describe1);
			break;
		case ButtonState::ChooseAct:
			window.draw(describe1);
			window.draw(describe2);
			window.draw(describe3);
			window.draw(describe4);
			break;
		case ButtonState::ChooseItem:
			window.draw(describe1);
			window.draw(describe2);
			window.draw(describe3);
			window.draw(describe4);
			break;
		case ButtonState::ChooseMercy:
			window.draw(describe1);
			window.draw(describe3);
			break;
		case ButtonState::Fight:
			window.draw(fightSprite);
			window.draw(fightLine);
			break;
		case ButtonState::Act:
			window.draw(describe1);
			window.draw(describe3);
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