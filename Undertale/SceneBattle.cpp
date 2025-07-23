#include "stdafx.h"
#include <fstream>
#include "SceneBattle.h"
#include "dialogueBox.h"
#include "BattleBox.h"
#include "json.hpp"
using json = nlohmann::json;

SceneBattle::SceneBattle()
	: Scene(SceneIds::Battle)
{
}

void SceneBattle::Init()
{
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	ANI_CLIP_MGR.Load("animations/fist.csv");
	texIds.push_back("graphics/spr_battlebg_0.png");
	texIds.push_back("graphics/spr_dumbtarget_0.png");
	texIds.push_back("graphics/spr_froggit_2.png");
	texIds.push_back("graphics/spr_dialogueBox.png");
	texIds.push_back("graphics/spr_fightbt_0.png");
	texIds.push_back("graphics/spr_fightbt_1.png");
	texIds.push_back("graphics/spr_actbt_0.png");
	texIds.push_back("graphics/spr_actbt_1.png");
	texIds.push_back("graphics/spr_itembt_0.png");
	texIds.push_back("graphics/spr_itembt_1.png");
	texIds.push_back("graphics/spr_sparebt_0.png");
	texIds.push_back("graphics/spr_sparebt_1.png");
	texIds.push_back("graphics/spr_heart_battle_pl_0.png");
	texIds.push_back("graphics/spr_hyperfist_0.png");
	texIds.push_back("graphics/spr_hyperfist_1.png");
	texIds.push_back("graphics/spr_hyperfist_2.png");
	texIds.push_back("graphics/spr_hyperfist_3.png");
	texIds.push_back("graphics/spr_hyperfist_4.png");
	texIds.push_back("graphics/spr_hyperfist_5.png");

	statusUI = (StatusInBattleUI*)AddGameObject(new StatusInBattleUI());
	statusUI->SetPosition({ windowSize.x * 0.02f, windowSize.y * 0.8f });

	fightButton = (BattleButton*)AddGameObject(new BattleButton());
	fightButton->SetTexIds("graphics/spr_fightbt_0.png", "graphics/spr_fightbt_1.png");
	fightButton->SetPosition({ windowSize.x * 0.02f, windowSize.y * 0.9f });
	actButton = (BattleButton*)AddGameObject(new BattleButton());
	actButton->SetTexIds("graphics/spr_actbt_0.png", "graphics/spr_actbt_1.png");
	actButton->SetPosition({ windowSize.x * 0.28f, windowSize.y * 0.9f });
	itemButton = (BattleButton*)AddGameObject(new BattleButton());
	itemButton->SetTexIds("graphics/spr_itembt_0.png", "graphics/spr_itembt_1.png");
	itemButton->SetPosition({ windowSize.x * 0.54f, windowSize.y * 0.9f });
	mercyButton = (BattleButton*)AddGameObject(new BattleButton());
	mercyButton->SetTexIds("graphics/spr_sparebt_0.png", "graphics/spr_sparebt_1.png");
	mercyButton->SetPosition({ windowSize.x * 0.8f, windowSize.y * 0.9f });

	soul = (Soul*)AddGameObject(new Soul());

	dialBox = (dialogueBox*)AddGameObject(new dialogueBox());

	btBox = (BattleBox*)AddGameObject(new BattleBox());

	Scene::Init();
}

void SceneBattle::Enter()
{
	// JSON 파일 불러오기
	std::ifstream file("jsons/frog.json");
	if (!file.is_open())
	{
		std::cerr << "파일 열기 실패\n";
	}
	json data;
	file >> data;

	dialBox->SetString(data["lines"][lineIndex]);
	btBox->startStr = data["startDescribe"];

	//
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();
	worldView.setSize(windowSize);
	worldView.setCenter(windowSize * 0.5f);

	Scene::Enter();

	background.setTexture(TEXTURE_MGR.Get("graphics/spr_battlebg_0.png"));
	Utils::SetOrigin(background, Origins::TC);
	background.setPosition({ windowSize.x * 0.5f,10.f });

	monster.setTexture(TEXTURE_MGR.Get("graphics/spr_froggit_2.png"));
	Utils::SetOrigin(monster, Origins::MC);
	monster.setPosition({ windowSize.x * 0.45f, windowSize.y * 0.4f });
}

void SceneBattle::Exit()
{
	Scene::Exit();
}

void SceneBattle::Update(float dt)
{
	Scene::Update(dt);

	if (isMyTurn)
	{
		if (btState == ButtonState::None)
		{
			if (InputMgr::GetKeyDown(sf::Keyboard::Z))
			{
				switch (btIndex)
				{
				case 0:
					btState = ButtonState::Fight;
					break;
				case 1:
					btState = ButtonState::Act;
					break;
				case 2:
					btState = ButtonState::Item;
					break;
				case 3:
					btState = ButtonState::Mercy;
					break;
				}
			}
			else
			{
				fightButton->UpdateTexture();
				actButton->UpdateTexture();
				itemButton->UpdateTexture();
				mercyButton->UpdateTexture();
			}
		}
	}
	else
	{

	}
}

void SceneBattle::Draw(sf::RenderWindow& window)
{
	window.draw(background);
	window.draw(monster);
	Scene::Draw(window);
}

void SceneBattle::SetMonsterTurn()
{
	soul->SetPosition({ size.x * 0.51f, size.y * 0.67f });
}
