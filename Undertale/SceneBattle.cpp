#include "stdafx.h"
#include <fstream>
#include "SceneBattle.h"
#include "BattleDialogueBox.h"
#include "BattleBox.h"
#include "Bullet.h"

SceneBattle::SceneBattle()
	: Scene(SceneIds::Battle)
{
}

void SceneBattle::Init()
{
	ANI_CLIP_MGR.Load("animations/fist.csv");
	texIds.push_back("graphics/spr_battlebg_0.png");
	texIds.push_back("graphics/spr_gun_bullet_.png");
	texIds.push_back("graphics/spr_bluespear.png");
	texIds.push_back("graphics/spr_eggbullet.png");
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
	statusUI->SetPosition({ size.x * 0.02f, size.y * 0.8f });

	fightButton = (BattleButton*)AddGameObject(new BattleButton());
	fightButton->SetTexIds("graphics/spr_fightbt_0.png", "graphics/spr_fightbt_1.png");
	fightButton->SetPosition({ size.x * 0.02f, size.y * 0.9f });
	actButton = (BattleButton*)AddGameObject(new BattleButton());
	actButton->SetTexIds("graphics/spr_actbt_0.png", "graphics/spr_actbt_1.png");
	actButton->SetPosition({ size.x * 0.28f, size.y * 0.9f });
	itemButton = (BattleButton*)AddGameObject(new BattleButton());
	itemButton->SetTexIds("graphics/spr_itembt_0.png", "graphics/spr_itembt_1.png");
	itemButton->SetPosition({ size.x * 0.54f, size.y * 0.9f });
	mercyButton = (BattleButton*)AddGameObject(new BattleButton());
	mercyButton->SetTexIds("graphics/spr_sparebt_0.png", "graphics/spr_sparebt_1.png");
	mercyButton->SetPosition({ size.x * 0.8f, size.y * 0.9f });

	btBox = (BattleBox*)AddGameObject(new BattleBox());
	soul = (Soul*)AddGameObject(new Soul());
	dialBox = (BattleDialogueBox*)AddGameObject(new BattleDialogueBox());

	Scene::Init();
}

void SceneBattle::Enter()
{
	// JSON 파일 불러오기
	std::ifstream file("jsons/frog.json");
	std::ifstream file2("jsons/testInventory.json");
	if (!file.is_open())
	{
		std::cerr << "파일 열기 실패\n";
	}
	if (!file2.is_open())
	{
		std::cerr << "파일2 열기 실패\n";
	}
	file >> data;
	file2 >> invenData;
	for (int i = 0; i < 4; i++)
	{
		std::string temp = invenData["items"][i]["itemId"];
		if (temp != "Null")
		{
			std::ifstream f(temp);
			f >> itemData[i];
		}		
	}

	dialBox->SetString(data["lines"][lineIndex]);
	lineCount = data["lines"].size();
	lineIndex = ++lineIndex % lineCount;
	btBox->startStr = data["startDescribe"];
	patternCount = data["attackPattern"].size();
	monsterTexId = data["texId"];
	monsterMaxHp = data["hp"];
	monsterHp = monsterMaxHp;
	actChooseCount = data["ActDescribe"].size();
	//
	worldView.setSize(size);
	worldView.setCenter(size * 0.5f);

	Scene::Enter();

	background.setTexture(TEXTURE_MGR.Get("graphics/spr_battlebg_0.png"));
	Utils::SetOrigin(background, Origins::TC);
	background.setPosition({ size.x * 0.5f,10.f });

	monster.setTexture(TEXTURE_MGR.Get(monsterTexId));
	Utils::SetOrigin(monster, Origins::MC);
	monster.setPosition({ size.x * 0.45f, size.y * 0.4f });
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
				dialBox->isDraw = false;
				switch (btIndex)
				{
				case 0:
					btState = ButtonState::ChooseFight;
					btBox->describeStr[0] = utf8_to_wstring(data["FightDescribe"]);
					break;
				case 1:
					btState = ButtonState::ChooseAct;
					actChooseIndex = 0;
					for (int i = 0; i < actChooseCount; ++i)
					{
						btBox->describeStr[i] = utf8_to_wstring(data["ActDescribe"][i]["act"]);
					}
					for (int i = actChooseCount; i < 4; ++i)
					{
						btBox->describeStr[i] = L"";
					}
					break;
				case 2:
					btState = ButtonState::ChooseItem;
					itemChooseIndex = 0;
					for (int i = 0; i < itemChooseCount; ++i)
					{
						std::string temp = invenData["items"][i]["itemId"];
						if (temp == "Null")
						{
							btBox->describeStr[i] = L"== 비어 있음 ==";
						}
						else
						{
							btBox->describeStr[i] = utf8_to_wstring(itemData[i]["name"]);
							healAmount[i] = itemData[i]["healAmount"];
						}
					}
					break;
				case 3:
					btState = ButtonState::ChooseMercy;
					mercyChooseIndex = 0;
					btBox->describeStr[0] = L"* 살려주기";
					btBox->describeStr[2] = L"* 도망";
					break;
				}
				soul->SetPosition({ size.x * 0.05f, size.y * 0.57f });
				btBox->UpdateBox();
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
		dialTimer += dt;
		turnTimer += dt;
		if (dialTimer >= dialExistTime)
		{
			dialTimer = 0.f;
			dialBox->isDraw = false;
		}
		if (turnTimer >= turnDuration)
		{
			turnTimer = 0.f;
			SetPlayerTurn();
		}
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
	isMyTurn = false;
	btState = ButtonState::None;
	btBox->SetBtBoxSize({ size.x * 0.4f, size.y * 0.25f });
	soul->SetPosition({ size.x * 0.51f, size.y * 0.67f });
	soul->SetBoundary(btBox->GetBoxGlobalBounds());
	dialBox->isDraw = true;
	dialBox->SetString(data["lines"][lineIndex]);
	lineIndex = ++lineIndex % lineCount;

	//
	int bulletCount = data["attackPattern"][PatternIndex]["bullets"].size();
	turnDuration = data["attackPattern"][PatternIndex]["duration"];
	for (int i = 0; i < bulletCount; ++i)
	{
		Bullet* b = (Bullet*)AddGameObject(new Bullet());
		bulletTemp.push_back(b);
		b->SetBulletState(data["attackPattern"][PatternIndex]["bullets"][i]["texId"],
			{ data["attackPattern"][PatternIndex]["bullets"][i]["PosX"], data["attackPattern"][PatternIndex]["bullets"][i]["PosY"] },
			{ data["attackPattern"][PatternIndex]["bullets"][i]["DirX"], data["attackPattern"][PatternIndex]["bullets"][i]["DirY"] },
			data["attackPattern"][PatternIndex]["bullets"][i]["speed"],
			data["attackPattern"][PatternIndex]["bullets"][i]["delay"],
			data["attackPattern"][PatternIndex]["bullets"][i]["damage"]
		);
		b->Reset();
	}

	PatternIndex = (PatternIndex + 1) % patternCount;
}

void SceneBattle::SetPlayerTurn()
{
	isMyTurn = true;
	soul->SetPosition({ size.x * 0.03f + size.x * 0.26f * btIndex, size.y * 0.93f });
	btBox->Reset();
	for (auto& b : bulletTemp)
	{
		RemoveGameObject(b);
	}
	bulletTemp.clear();
}

void SceneBattle::SetActDescribe()
{
	btBox->describeStr[0] = utf8_to_wstring(data["ActDescribe"][actChooseIndex]["describes"][0]["describe"]);
	btBox->describeStr[2] = utf8_to_wstring(data["ActDescribe"][actChooseIndex]["describes"][1]["describe"]);
	btBox->UpdateBox();
	
	mercyPoint += data["ActDescribe"][actChooseIndex]["mercyPoint"];
}

void SceneBattle::TryUseItem()
{
	// "jsons/TestItem.json"
	if (!itemData[itemChooseIndex].empty())
	{
		int amount = itemData[itemChooseIndex]["healAmount"];
		invenData["items"][itemChooseIndex]["itemId"] = "Null";
		soul->hp = Utils::ClampInt(soul->hp + amount, 0, soul->maxHp);
		statusUI->UpdateHpUI();
		SetMonsterTurn();
		itemData[itemChooseIndex].clear();
	}
}

void SceneBattle::TryMercy()
{
	if (mercyChooseIndex == 0 && mercyPoint >= mercyCanPoint)
	{
		std::cout << "살려주기 실행" << std::endl;
	}
	else if (mercyChooseIndex == 1)
	{
		std::cout << "도망가기 실행" << std::endl;
	}
}
