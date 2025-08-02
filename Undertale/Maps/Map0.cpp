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
	texIds.push_back("graphics/spr_smallfrog_0.png");
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

	//
	frog = (TalkObject*)AddGameObject(new TalkObject("frog"));
	frog->SetTexId("graphics/spr_smallfrog_0.png");
	frog->SetPosition({ 630.f,288.f });
	frog->lines.push_back(L"* 개굴, 개굴.\n* (넌 꽤 자비롭게\n  보이네, 인간치고는...)");
	frog->lines.push_back(L"* (괴물들을 살려줄 수\n  있을때, 노란색 글자로\n  보여.)");
	frog->lines.push_back(L"* (어떻게 생각해?\n  유용하지?)");

	frog2 = (TalkObject*)AddGameObject(new TalkObject("frog2"));
	frog2->SetTexId("graphics/spr_smallfrog_0.png");
	frog2->SetPosition({ 242.f,216.f });
	frog2->lines.push_back(L"* 개굴, 개굴.\n* (오랜 만에 떨어진 인간이네.)");
	frog2->lines.push_back(L"* (이 앞으로 가면 괴물들과\n  싸우게 될 수 도 있어. 조심해.)");
	frog2->lines.push_back(L"* (모두 나처럼 순한건 아니니까.)");

	soundIds.push_back("sounds/SND_TXT1.wav");
	texIds.push_back("graphics/TextWindow.png");
	textWindow = (TextWindow*)AddGameObject(new TextWindow("textWindow"));
	//
	Scene::Init();
}

void Map0::Enter()
{
	InventoryUi::healItem[0].SetInfo(L"", 0); // 아이템 이름과 회복량 설정
	InventoryUi::healItem[1].SetInfo(L"", 0);
	InventoryUi::healItem[2].SetInfo(L"", 0);
	InventoryUi::healItem[3].SetInfo(L"", 0);


	Scene::LoadMapFromJson("map0.json", "map0", player, background, objects, hitboxes);

	Scene::Enter();
	sf::Vector2f size = {640.f, 480.f};
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	worldView.setSize(size * 0.5f);
	uiView.setSize(size);
	uiView.setCenter(center);

	player->SetPosition(startPos);

	SOUND_MGR.PlayBgm("sounds/05 Ruins.flac");
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
			else if (hit.type == "SceneChanege")
			{
				std::cout << "씬 전환 트리거됨!" << std::endl;
				startPos = player->GetPosition() + sf::Vector2f(0.f,10.f);
				SCENE_MGR.ChangeScene(SceneIds::Map1);
			}			
		}
	}
	
	Scene::Update(dt);
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
