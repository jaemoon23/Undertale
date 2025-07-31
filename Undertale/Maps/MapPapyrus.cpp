#include "stdafx.h"
#include "MapPapyrus.h"
#include "Player.h"
#include "Papyrus.h"

#include <fstream>
#include "json.hpp"
#include "TextGo.h"

#include "DialogueBox.h"
#include "UiChanger.h"
#include "InventoryUi.h"
#include "PlayerInfoUi.h"
#include "HealItem.h"
#include <SceneBattle.h>


MapPapyrus::MapPapyrus() : Scene(SceneIds::MapPapyrus)
{
}

void MapPapyrus::Init()
{
	texIds.push_back("Sprites/idle.png");
	texIds.push_back("graphics/PapyrusBack.png");
	texIds.push_back("Sprites/downwalking.png");
	texIds.push_back("Sprites/upwalking.png");
	texIds.push_back("Sprites/leftwalking.png");
	texIds.push_back("Sprites/rightwalking.png");
	texIds.push_back("Sprites/sprite_sheet_papyrus_cape.png");
	texIds.push_back("Sprites/spr_papyrus_cape_0.png");	
	texIds.push_back("Sprites/spr_rainbowtarget_0.png");
	texIds.push_back("Sprites/sprite_sheet_papyrus_toasted.png");
	texIds.push_back("Sprites/sprite_sheet_papyrus_run.png");

	texIds.push_back("Sprites/spr_heart_battle_pl_0.png");
	texIds.push_back("Sprites/backgroundui.png");

	ANI_CLIP_MGR.Load("Animation/idle.csv");
	ANI_CLIP_MGR.Load("Animation/downwalking.csv");
	ANI_CLIP_MGR.Load("Animation/upwalking.csv");
	ANI_CLIP_MGR.Load("Animation/leftwalking.csv");
	ANI_CLIP_MGR.Load("Animation/rightwalking.csv");
	ANI_CLIP_MGR.Load("Animation/papyrusidle.csv");
	ANI_CLIP_MGR.Load("Animation/papyrustoasted.csv");
	ANI_CLIP_MGR.Load("Animation/papyrusrun.csv");
	

	player = (Player*)AddGameObject(new Player("Sprites/idle.png"));
	papyrus = (Papyrus*)AddGameObject(new Papyrus("papyrus"));
	//exclamationmark.setTexture(TEXTURE_MGR.Get("Sprites/spr_rainbowtarget_0.png"));

	background = (SpriteGo*)AddGameObject(new SpriteGo());
	background->sortingLayer = SortingLayers::Background;

	exclamationmark = (SpriteGo*)AddGameObject(new SpriteGo("spr_rainbowtarget_0"));
	exclamationmark->SetTextureId("Sprites/spr_rainbowtarget_0.png");
	exclamationmark->sortingLayer = SortingLayers::Foreground; // ���ϴ� layer�� ����
	exclamationmark->sortingOrder = 1;
	

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

	Scene::Init();
}

void MapPapyrus::Enter()
{
	doorwall.setSize({ 1200.f,20.f });
	doorwall.setFillColor(sf::Color::Transparent);
	doorwall.setOutlineColor(sf::Color::Transparent);
	doorwall.setOutlineThickness(1.f);
	doorwall.setPosition({ 470.f, 403.f });



	std::ifstream in("map6.json");
	if (!in)
	{
		std::cerr << "map6.json ������ �� �� �����ϴ�!" << std::endl;
		return;
	}

	nlohmann::json j;
	in >> j;
	auto& mapData = j["map6"];

	// ���
	std::string bgTex = mapData["background"]["textureId"];
	sf::Vector2f bgPos(mapData["background"]["position"][0], mapData["background"]["position"][1]);
	sf::Vector2f scale(mapData["background"]["scale"][0], mapData["background"]["scale"][1]);

	background->SetTextureId(bgTex);
	background->SetOrigin(Origins::MC);
	background->SetPosition(bgPos);
	background->SetScale(scale);
	Scene::Enter();

	sf::Vector2f size = { 640.f, 480.f };
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	worldView.setSize(size * 0.5f);
	uiView.setSize(size);
	uiView.setCenter(center);

	// ������Ʈ
	if (!BattleEnd)
	{
		bool playerPlaced = false;
		for (auto& obj : mapData["objects"])
		{
			std::string texId = obj["textureId"];
			sf::Vector2f pos(obj["position"][0], obj["position"][1]);
			sf::Vector2f scale(1.f, 1.f);
			if (obj.contains("scale"))
				scale = { obj["scale"][0], obj["scale"][1] };

			if (!playerPlaced)
			{
				player->SetOrigin(Origins::MC);
				player->SetPosition(pos);
				playerPlaced = true;
			}
			else
			{
				auto sprite = new SpriteGo(texId);
				sprite->SetTextureId(texId);
				sprite->SetOrigin(Origins::MC);
				sprite->SetPosition(pos);
				sprite->SetScale(scale);
				sprite->Reset();
				AddGameObject(sprite);
				testObjects.push_back(sprite);
			}
		}
	}
	

	//  ��Ʈ�ڽ� �ε�
	for (auto& box : mapData["hitboxes"])
	{
		sf::Vector2f pos(box["position"][0], box["position"][1]);
		sf::Vector2f size(box["size"][0], box["size"][1]);
		std::string typeStr = box["type"];

		auto rect = new sf::RectangleShape(size);
		rect->setPosition(pos);
		rect->setFillColor(sf::Color::Transparent);

		if (typeStr == "Wall")
		{
			rect->setOutlineColor(sf::Color::Green);
		}
		else if (typeStr == "SceneChanege")
		{
			rect->setOutlineColor(sf::Color(128, 0, 128));
		}
		else if (typeStr == "NextScene")
		{
			rect->setOutlineColor(sf::Color(255, 165, 0));
		}
		else if (typeStr == "PrevScene")
		{
			rect->setOutlineColor(sf::Color(135, 206, 250));
		}
		else if (typeStr == "Battle")
		{
			rect->setOutlineColor(sf::Color::Red);
		}

		rect->setOutlineThickness(1.f);
		hitboxes.push_back({ rect, typeStr });
	}

	papyrus->SetPosition({ 430, 350 });

	if (BattleEnd && !papyrusImageChange)
	{
		if (PlayerInfo::lv >= 15) 
		{
			papyrus->animator.Play("Animation/papyrustoasted.csv");
			papyrusImageChange = true;
			doorwall.setSize({ 0,0 });
			doorwall.setPosition({ 1000,1000 });
		}
	}

	if (BattleEnd && !papyrusImageChange && !papyrusMercy)
	{
		papyrus->animator.Play("Animation/papyrusidle.csv");
		papyrusMercy = true;
	}

}

void MapPapyrus::Update(float dt)
{
	worldView.setCenter(player->GetPosition());
	battleCheckTimer += dt;
	if (InputMgr::GetKeyDown(sf::Keyboard::Return))
	{
		std::cout << player->GetPosition().x << ", " << player->GetPosition().y << std::endl;
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
				std::cout << "�� ��ȯ Ʈ���ŵ�!" << std::endl;
				SCENE_MGR.ChangeScene(SceneIds::Dev1);
			}
			else if (hit.type == "NextScene")
			{
				std::cout << "NextScene" << std::endl;
				SCENE_MGR.ChangeScene(SceneIds::MapSans);
			}
			else if (hit.type == "PrevScene")
			{
				std::cout << "PrevScene" << std::endl;
				SCENE_MGR.ChangeScene(SceneIds::Map5);
			}
		}
	}
	if (!dialogueTriggered)
	{
		sf::Vector2f playerPos = player->GetPosition();
		sf::Vector2f papyrusPos = papyrus->GetPosition();
		float distance = Utils::Distance(playerPos, papyrusPos);

		if (distance < 100.f)
		{
			isexclamationmarkActive = true;
			exclamationmark->SetPosition({ 419, 300 });

			dialogueTriggered = true;
			player->PapyrusInteract();
			player->SetMove(false);
			player->animator.Stop();

			exclamationmarkTimer = 0.f; // Ÿ�̸� �ʱ�ȭ 
		}
	}

	else if (dialogueTriggered && !dialogueEnd && !dialoguebox->GetActive())
	{
		dialogueEnd = true;
		player->SetMove(true);
	}

	if (isexclamationmarkActive)
	{
		exclamationmarkTimer += dt;
		if (exclamationmarkTimer >= 1.f)
		{
			isexclamationmarkActive = false;
			exclamationmark->SetActive(false);
		}
	}

	if (Utils::CheckCollision(player->GetHitBox(), papyrus->GetHitBox()))
	{
		player->SetPosition(player->getPos());
	}

	sf::Vector2f playerPos = player->GetPosition();
	sf::Vector2f papyrusPos = papyrus->GetPosition();
	float distance = Utils::Distance(playerPos, papyrusPos);

	if (distance <= 30.f && InputMgr::GetKeyDown(sf::Keyboard::Z) && !BattleEnd)
	{
		SceneBattle::nextSceneId = SceneIds::MapPapyrus;
		SceneBattle::monsterJsonID = "jsons/papyrus.json";
		SCENE_MGR.ChangeScene(SceneIds::Battle);
		BattleEnd = true;
	}




	if (BattleEnd && papyrusImageChange && !papyrusLastInteract)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::Z))
		{
			player->PapyrusBattleEndInteract();
			player->SetMove(false);
			player->animator.Stop();
			papyrusLastInteract = true;
		}
	}



	if (BattleEnd && !papyrusImageChange && papyrusMercy && !mercyDialogEnd)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::Z))
		{
			player->PapyrusMercyInteract();
			player->SetMove(false);
			player->animator.Stop();
			mercyDialogEnd = true;
		}
	}



	if (!dialoguebox->GetActive() && papyrusLastInteract)
	{
		player->SetMove(true);
		papyrus->animator.Play("Animation/papyrusrun.csv");

		sf::Vector2f papyrusPos = papyrus->GetPosition();
		sf::Vector2f direction = { 1.f,0.f };
		Utils::Normalize(direction);
		float sansSpeed = 150.f;
		papyrusPos += direction * sansSpeed * dt;
		papyrus->SetPosition(papyrusPos);
	}

	if (!dialoguebox->GetActive() && papyrusMercy && mercyDialogEnd)
	{
		player->SetMove(true);
		papyrus->animator.Play("Animation/papyrusrun.csv");

		sf::Vector2f papyrusPos = papyrus->GetPosition();
		sf::Vector2f direction = { 1.f,0.f };
		Utils::Normalize(direction);
		float sansSpeed = 150.f;
		papyrusPos += direction * sansSpeed * dt;
		papyrus->SetPosition(papyrusPos);
	}

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

	if (dialoguebox && dialoguebox->GetActive())
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::Z))
		{
			dialoguebox->NextLine();
		}
	}

	if (Utils::CheckCollision(player->GetHitBox(), doorwall))
	{
		player->SetPosition(player->getPos());
	}


	Scene::Update(dt);
}

void MapPapyrus::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.setView(worldView);
	//window.setView(uiView);
	if (isexclamationmarkActive)
	{
		exclamationmark->Draw(window);
	}

	if (Variables::isDrawHitBox)
	{
		for (auto& hit : hitboxes)
		{
			window.draw(*hit.shape); // worldView �������� �׷���
		}
	}
	window.draw(doorwall);
}

