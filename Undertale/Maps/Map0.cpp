#include "stdafx.h"
#include "Map0.h"
#include <fstream>
#include "json.hpp"
#include "Player.h"
#include "SceneBattle.h"
#include "TextGo.h"

#include "UiChanger.h"
#include "Sans.h"
#include "InventoryUi.h"
#include "DialogueBox.h"
#include "PlayerInfoUi.h"
#include "HealItem.h"

Map0::Map0() : Scene(SceneIds::Map0)
{
}
void Map0::Init()
{
	fontIds.push_back("fonts/DungGeunMo.ttf");
	texIds.push_back("Sprites/idle.png");
	texIds.push_back("Sprites/downwalking.png");
	texIds.push_back("Sprites/upwalking.png");
	texIds.push_back("Sprites/leftwalking.png");
	texIds.push_back("Sprites/rightwalking.png");
	texIds.push_back("Sprites/backgroundui.png");
	texIds.push_back("Sprites/bg_asgore_livingroom_0.png");
	texIds.push_back("Sprites/spr_sans_sleep_0.png");
	texIds.push_back("graphics/bg_innrooms_0.png");
	texIds.push_back("graphics/bg_firstroom.png");
	texIds.push_back("graphics/spr_cutetable_0.png");
	texIds.push_back("Sprites/spr_heart_battle_pl_0.png");

	ANI_CLIP_MGR.Load("Animation/idle.csv");
	ANI_CLIP_MGR.Load("Animation/downwalking.csv");
	ANI_CLIP_MGR.Load("Animation/upwalking.csv");
	ANI_CLIP_MGR.Load("Animation/leftwalking.csv");
	ANI_CLIP_MGR.Load("Animation/rightwalking.csv");

	player = (Player*)AddGameObject(new Player("Sprites/idle.png"));
	
	inventoryui = new InventoryUi("InventoryUi");
	dialoguebox = new DialogueBox("dialoguebox");
	uichanger = new UiChanger("uichanger");
	playerinfoui = new PlayerInfoUi("playerinfoui");

	background = (SpriteGo*)AddGameObject(new SpriteGo());
	background->sortingLayer = SortingLayers::Background;
	
	player->SetBox(dialoguebox);
	player->SetUiChanger(uichanger);
	player->SetInventoryUi(inventoryui);
	player->SetPlayerInfoUi(playerinfoui);
	dialoguebox->SetPlayer(player);
	uichanger->SetPlayer(player);
	uichanger->SetInventoryUi(inventoryui);
	uichanger->SetPlayerInfoUi(playerinfoui);
	inventoryui->SetPlayer(player);
	inventoryui->SetBox(dialoguebox);
	
	AddGameObject(inventoryui);
	AddGameObject(dialoguebox);
	AddGameObject(uichanger);
	AddGameObject(playerinfoui);
	Scene::Init();
}

void Map0::Enter()
{
	InventoryUi::healItem[0].SetInfo(L"", 0); // 아이템 이름과 회복량 설정
	InventoryUi::healItem[1].SetInfo(L"", 0);
	InventoryUi::healItem[2].SetInfo(L"", 0);
	InventoryUi::healItem[3].SetInfo(L"", 0);

	SOUND_MGR.StopBgm();

	Scene::LoadMapFromJson("map0.json", "map0", player, background, objects, hitboxes);

	Scene::Enter();
	sf::Vector2f size = {640.f, 480.f};
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	worldView.setSize(size * 0.5f);
	uiView.setSize(size);
	uiView.setCenter(center);

	player->SetPosition(startPos);
}
void Map0::Update(float dt)
{
	worldView.setCenter(player->GetPosition());
	battleCheckTimer += dt;

	if (InputMgr::GetKeyDown(sf::Keyboard::C))
	{
		if ((inventoryui && inventoryui->GetActive()) ||
			(playerinfoui && playerinfoui->GetActive()) ||
			(dialoguebox && dialoguebox->GetActive()))
		{
			return;
		}
		uichanger->SetActive(!uichanger->GetActive());
	}

	for (auto& hit : hitboxes)
	{
		if (Utils::CheckCollision(player->GetHitBox(), *hit.shape))
		{
			if (hit.type == "Wall")
			{
				player->SetPosition(player->getPos());
			}
			else if (hit.type == "SceneChange")
			{
				std::cout << "씬 전환 트리거됨!" << std::endl;
				startPos = player->GetPosition() + sf::Vector2f(0.f,10.f);
				SCENE_MGR.ChangeScene(SceneIds::Map1);
			}			
		}
	}
	
	//Scene::Update(dt);
	player->Update(dt);
	playerinfoui->Update(dt);
	inventoryui->Update(dt);
	uichanger->Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Return))
	{
		std::cout << player->GetPosition().x << ", " << player->GetPosition().y << std::endl;
	}
}

void Map0::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.setView(worldView);
	
	
	if (Variables::isDrawHitBox)
	{
		for (auto& hit : hitboxes)
		{
			window.draw(*hit.shape); // worldView 기준으로 그려짐
		}
	}
}
