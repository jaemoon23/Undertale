#include "stdafx.h"
#include "Map3.h"
#include "Player.h"
#include "SceneBattle.h"

#include "DialogueBox.h"
#include "UiChanger.h"
#include "InventoryUi.h"
#include "PlayerInfoUi.h"
#include "HealItem.h"

Map3::Map3() : Scene(SceneIds::Map3)
{
}

void Map3::Init()
{	
	fontIds.push_back("fonts/DungGeunMo.ttf");
	texIds.push_back("graphics/spr_savepoint_0.png");
	texIds.push_back("graphics/spr_notepaper_0.png");
	texIds.push_back("graphics/spr_mousehole_0.png");
	texIds.push_back("graphics/spr_microwave_0.png");
	texIds.push_back("graphics/spr_spaghetti_0.png");
	texIds.push_back("Sprites/idle.png");
	texIds.push_back("graphics/back4.png");
	texIds.push_back("Sprites/downwalking.png");
	texIds.push_back("Sprites/upwalking.png");
	texIds.push_back("Sprites/leftwalking.png");
	texIds.push_back("Sprites/rightwalking.png");
	texIds.push_back("Sprites/spr_heart_battle_pl_0.png");
	texIds.push_back("Sprites/backgroundui.png");
	
	soundIds.push_back("sounds/snd_heal_c.wav");
	soundIds.push_back("sounds/17 Snowy.flac");
	ANI_CLIP_MGR.Load("Animation/idle.csv");
	ANI_CLIP_MGR.Load("Animation/downwalking.csv");
	ANI_CLIP_MGR.Load("Animation/upwalking.csv");
	ANI_CLIP_MGR.Load("Animation/leftwalking.csv");
	ANI_CLIP_MGR.Load("Animation/rightwalking.csv");

	player = (Player*)AddGameObject(new Player("Sprites/idle.png"));
	background = (SpriteGo*)AddGameObject(new SpriteGo());
	background->sortingLayer = SortingLayers::Background;

	inventoryui = new InventoryUi("InventoryUi");
	dialoguebox = new DialogueBox("dialoguebox");
	uichanger = new UiChanger("uichanger");
	playerinfoui = new PlayerInfoUi("playerinfoui");

	player->SetBox(dialoguebox);
	player->SetUiChanger(uichanger);
	player->SetInventoryUi(inventoryui);
	player->SetPlayerInfoUi(playerinfoui);
	dialoguebox->SetPlayer(player);
	uichanger->SetDialogueBox(dialoguebox);
	uichanger->SetPlayer(player);
	uichanger->SetInventoryUi(inventoryui);
	uichanger->SetPlayerInfoUi(playerinfoui);
	inventoryui->SetPlayer(player);
	inventoryui->SetBox(dialoguebox);

	AddGameObject(inventoryui);
	AddGameObject(dialoguebox);
	AddGameObject(uichanger);
	AddGameObject(playerinfoui);

	player->SetBox(dialoguebox);
	dialoguebox->SetPlayer(player);

	// 상호작용 오브젝트 넣는 법
	spaghetti = (TalkObject*)AddGameObject(new TalkObject("spaghetti"));
	spaghetti->SetTexId("graphics/spr_spaghetti_0.png");
	spaghetti->SetPosition({ 320.f,235.f });
	spaghetti->lines.push_back(L"* (냉동 스파게티\n  한 그릇이다.)");
	spaghetti->lines.push_back(L"* (너무 차가워서,\n  테이블에 붙어버렸다...)");
	
	microwave = (TalkObject*)AddGameObject(new TalkObject("microwave"));
	microwave->SetTexId("graphics/spr_microwave_0.png");
	microwave->SetPosition({ 370.f,235.f });
	microwave->lines.push_back(L"* (플러그가 뽑힌\n  전자렌지이다.)");
	microwave->lines.push_back(L"* (모든 버튼이\n  '스파게티'이다.)");

	notepaper = (TalkObject*)AddGameObject(new TalkObject("notepaper"));
	notepaper->SetTexId("graphics/spr_notepaper_0.png");
	notepaper->SetPosition({ 270.f,240.f });
	notepaper->lines.push_back(L"* 누군가가 남긴\n  쪽지다...");
	notepaper->lines.push_back(L"인간!! 이 스파게티를\n즐겨주길 바란다.");
	notepaper->lines.push_back(L"(넌 잘 모르겠지만,\n이 스파게티는...)");
	notepaper->lines.push_back(L"(널 꾀어내기 위한\n함정이다!!!)");
	notepaper->lines.push_back(L"(먹느라 너무 바빠서...)");
	notepaper->lines.push_back(L"(네가 앞으로 나아가고\n있지 않다는 것도\n알아채지 못하겠지!!!)");
	notepaper->lines.push_back(L"(위대한 파피루스님에게\n또 철저히\n농락당했군!!!)");
	notepaper->lines.push_back(L"\n      녜- 헤- 헤,\n             파피루스");

	mousehole = (TalkObject*)AddGameObject(new TalkObject("mousehole"));
	mousehole->SetTexId("graphics/spr_mousehole_0.png");
	mousehole->SetPosition({ 310.f,178.f });
	mousehole->lines.push_back(L"* 쥐 구멍이다.");

	savepoint = (TalkObject*)AddGameObject(new TalkObject("savepoint"));
	savepoint->SetTexId("graphics/spr_savepoint_0.png");
	savepoint->SetPosition({ 320.f,310.f });
	savepoint->lines.push_back(L"* (쥐가 언젠가는 스파게티를\n  데울 방법을 찾으리라는\n  걸 알고 있기에...)");
	savepoint->lines.push_back(L"* (당신의 의지가 충만해진다.)");

	soundIds.push_back("sounds/SND_TXT1.wav");
	texIds.push_back("graphics/TextWindow.png");
	textWindow = (TextWindow*)AddGameObject(new TextWindow("textWindow"));
	//

	Scene::Init();
}

void Map3::Enter()
{
	Scene::LoadMapFromJson("map3.json", "map3", player, background, objects, hitboxes);
	Scene::Enter();

	sf::Vector2f size = { 640.f, 480.f };
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	worldView.setSize(size * 0.5f);
	uiView.setSize(size);
	uiView.setCenter(center);

	//SOUND_MGR.PlayBgm("sounds/17 Snowy.flac");

	player->SetPosition(startPos);
	worldView.setCenter(size * 0.5f);
}

void Map3::Update(float dt)
{
	// 테스트 코드
	if (InputMgr::GetKeyDown(sf::Keyboard::Numpad5))
	{
		SceneBattle::nextSceneId = SceneIds::Map3;
		SceneBattle::monsterJsonID = "jsons/migosp.json";
		startPos = player->GetPosition();
		player->StartBattle();
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Return))
	{
		std::cout << player->GetPosition().x << ", " << player->GetPosition().y << std::endl;
	}
	//

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
			else if (hit.type == "Battle")
			{
				if (battleCheckTimer >= battleCheckInterval)
				{
					battleCheckTimer = 0.f;

					// 1% 확률
					if (player->GetMove() && Utils::RandomRange(0.f, 1.f) < 0.01f)
					{
						SceneBattle::nextSceneId = SceneIds::Map3;
						SceneBattle::monsterJsonID = "jsons/migosp.json";
						startPos = player->GetPosition();
						player->StartBattle();
					}
				}
			}
			else if (hit.type == "Switch")
			{
				std::cout << "Switch" << std::endl;
				if (InputMgr::GetKeyDown(sf::Keyboard::Z))
				{
					puzzleSuccess = true;
				}
			}
			else if (hit.type == "NextScene")
			{
				std::cout << "NextScene" << std::endl;
				startPos = player->GetPosition() + sf::Vector2f(-15.f, 0.f);
				SCENE_MGR.ChangeScene(SceneIds::Map4);
			}
			else if (hit.type == "PrevScene")
			{
				std::cout << "PrevScene" << std::endl;
				startPos = { 214.f,267.f };
				SCENE_MGR.ChangeScene(SceneIds::Map2);
			}
			else if (hit.type == "Signs")
			{
				std::cout << "Signs" << std::endl;
			}
		}
	}
	Scene::Update(dt);
}

void Map3::Draw(sf::RenderWindow& window)
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

