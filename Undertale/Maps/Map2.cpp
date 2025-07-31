#include "stdafx.h"
#include "Map2.h"
#include "Player.h"
#include "SceneBattle.h"
#include "DialogueBox.h"

#include <fstream>
#include "json.hpp"
#include "TextGo.h"
#include "Sans.h"

#include "UiChanger.h"
#include "InventoryUi.h"
#include "PlayerInfoUi.h"
#include "HealItem.h"
#include "GameObject.h"

static sf::Texture tex1, tex2;
static sf::Texture tex3, tex4;

Map2::Map2() : Scene(SceneIds::Map2)
{
}

void Map2::Init()
{
	font.loadFromFile("fonts/DungGeunMo.ttf");

	texIds.push_back("Sprites/idle.png");
	texIds.push_back("Sprites/spr_f_maincharar_0.png");
	texIds.push_back("graphics/back3.png");
	texIds.push_back("Sprites/downwalking.png");
	texIds.push_back("Sprites/upwalking.png");
	texIds.push_back("Sprites/leftwalking.png");
	texIds.push_back("Sprites/rightwalking.png");
	texIds.push_back("Sprites/sprite_sheet_dark.png");
	texIds.push_back("Sprites/spr_sans_r_dark_2.png");
	texIds.push_back("Sprites/spr_heart_battle_pl_0.png");
	texIds.push_back("Sprites/backgroundui.png");
	texIds.push_back("Sprites/spr_sans_sleep_0.png");
	texIds.push_back("Sprites/spr_f_maincharad_0.png");
	texIds.push_back("Sprites/spr_f_maincharal_0.png");
	texIds.push_back("Sprites/spr_sans_r_0.png");
	texIds.push_back("Sprites/spr_sans_r_darkhand_2.png");
	texIds.push_back("Sprites/spr_sans_r_dark_0.png");


	images.clear();
	tex1.loadFromFile("Sprites/spr_f_maincharad_0.png");
	tex2.loadFromFile("Sprites/spr_f_maincharal_0.png");
	images.push_back(&tex1);
	images.push_back(&tex2);


	ANI_CLIP_MGR.Load("Animation/idle.csv");
	ANI_CLIP_MGR.Load("Animation/downwalking.csv");
	ANI_CLIP_MGR.Load("Animation/upwalking.csv");
	ANI_CLIP_MGR.Load("Animation/leftwalking.csv");
	ANI_CLIP_MGR.Load("Animation/rightwalking.csv");
	ANI_CLIP_MGR.Load("Animation/sansdarkwalking.csv");


	player = (Player*)AddGameObject(new Player("Sprites/idle.png"));
	sans = (Sans*)AddGameObject(new Sans("Sprites/spr_sans_r_dark_2.png"));

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
	player->SetSans(sans);
	inventoryui->SetBox(dialoguebox);


	AddGameObject(inventoryui);
	AddGameObject(dialoguebox);
	AddGameObject(uichanger);
	AddGameObject(playerinfoui);

	player->SetBox(dialoguebox);
	dialoguebox->SetPlayer(player);
	player->SetSans(sans);

	background2 = (SpriteGo*)AddGameObject(new SpriteGo());
	background2->sortingLayer = SortingLayers::Background;

	Scene::Init();
}

void Map2::Enter()
{
	float imageChangeTimer = 0.f;
	int currentImageIndex = 0;

	int playerImageIndex = 0;
	int sansImageIndex = 0;

	animationPlay = false;
	InteractedSans = false;
	firstInteractedEnds = false;
	imageChangedOnce = false;

	afterTurnTimer = 0.f;
	charaTurn = false;

	reactivateTimer = 0.f;
	reactivated = false; // 플레이어와 샌즈가 다시 active 할때 

	sansSecondInteractTimer = 0.f; // 샌즈와 다시 대화할 때 
	isWaitingSansSecondInteract = false;
	wallDisabled = false;

	isPlayerColliding = false;

	doorwall.setSize({ 14.f,100.f });
	doorwall.setFillColor(sf::Color::Transparent);
	doorwall.setOutlineColor(sf::Color::Transparent);
	doorwall.setOutlineThickness(1.f);
	doorwall.setPosition({ 470.f, 305.f });

	std::ifstream in("map2.json");
	if (!in)
	{
		std::cerr << "map1.json 파일을 열 수 없습니다!" << std::endl;
		return;
	}

	nlohmann::json j;
	in >> j;
	auto& mapData = j["map2"];

	// 배경
	std::string bgTex = mapData["background"]["textureId"];
	sf::Vector2f bgPos(mapData["background"]["position"][0], mapData["background"]["position"][1]);
	sf::Vector2f scale(mapData["background"]["scale"][0], mapData["background"]["scale"][1]);

	background2->SetTextureId(bgTex);
	background2->SetOrigin(Origins::MC);
	background2->SetPosition(bgPos);
	background2->SetScale(scale);
	Scene::Enter();

	sf::Vector2f size = { 640.f, 480.f };
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	worldView.setSize(size * 0.5f);
	uiView.setSize(size);
	uiView.setCenter(center);

	// 오브젝트
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

	//  히트박스 로드
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
		else
		{
			rect->setOutlineColor(sf::Color::Green);
		}
		rect->setOutlineThickness(1.f);
		hitboxes.push_back({ rect, typeStr });

	}
	sans->SetPosition({ 220.f, 355.f });
	sans->SetActive(false);

	uiView.setSize(size);
	uiView.setCenter(center);
}

void Map2::Update(float dt)
{
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
		if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
		{
			dialoguebox->NextLine();
		}
	}
	worldView.setCenter(player->GetPosition());
	battleCheckTimer += dt;

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
				if (isBattleInetrected)
				{
					if (battleCheckTimer >= battleCheckInterval)
					{
						std::cout << "배틀 확률 체크" << std::endl;
						battleCheckTimer = 0.f;

						// 1% 확률
						if (Utils::RandomRange(0.f, 1.f) < 0.01f)
						{
							std::cout << "랜덤 전투 발생!" << std::endl;
							SceneBattle::nextSceneId = SceneIds::Map2;
							SceneBattle::monsterJsonID = "jsons/whimsun.json";
							player->StartBattle();
						}
						else
						{
							std::cout << "배틀 아님" << std::endl;
						}
					}
				}

			}
			else if (hit.type == "NextScene")
			{
				std::cout << "NextScene" << std::endl;
				SCENE_MGR.ChangeScene(SceneIds::Map3);
			}
			else if (hit.type == "PrevScene")
			{
				std::cout << "PrevScene" << std::endl;
				SCENE_MGR.ChangeScene(SceneIds::Map1);
			}
		}
	}

	if (Utils::CheckCollision(player->GetHitBox(), doorwall))
{
    // 처음 충돌 시 설정
    if (!animationPlay)
    {
        player->SetMove(false);
        player->animator.Stop();
        isBattleInetrected = false;
        player->GetSprite().setTexture(TEXTURE_MGR.Get("Sprites/spr_f_maincharar_0.png"));
        sans->SetActive(true);
        sans->animator.Play("Animation/sansdarkwalking.csv");
        animationPlay = true;
    }

    // Sans 이동
    sf::Vector2f sansPos = sans->GetPosition();
    sf::Vector2f playerPos = player->GetPosition();
    sf::Vector2f direction = playerPos - sansPos;
    Utils::Normalize(direction);
    float sansSpeed = 100.f;
    sansPos += direction * sansSpeed * dt;
    sans->SetPosition(sansPos);

    // 플레이어와 Sans 간 충돌 시 대화 처리
    if (Utils::CheckCollision(player->GetHitBox(), sans->GetHitBox()))
    {
       
        if (!InteractedSans)
        {
            InteractedSans = true;
			sans->SetMove(false);
			sans->animator.Stop();
            player->SansInteract();

        }

        if (InputMgr::GetKeyDown(sf::Keyboard::Z))
        {
            dialoguebox->NextLine();
        }
    }

    // 대화 종료 후 플래그 설정
    if (InteractedSans && !firstInteractedEnds && !dialoguebox->GetActive())
    {
        firstInteractedEnds = true;
        imageChangeTimer = 0.f;
    }

    // [Phase 1] 플레이어 이미지 변경 (대화 종료 후 2초)
    if (firstInteractedEnds && !imageChangedOnce)
    {
        imageChangeTimer += dt;
        if (imageChangeTimer >= 2.f)
        {
            imageChangeTimer = 0.f;
            playerImageIndex = (playerImageIndex + 1) % images.size();
            player->GetSprite().setTexture(*images[playerImageIndex]);
            sf::Vector2u texSize = images[playerImageIndex]->getSize();
            player->GetSprite().setTextureRect(sf::IntRect(0, 0, texSize.x, texSize.y));

            imageChangedOnce = true;
            // Phase 2 시작을 위한 타이머 초기화
            afterTurnTimer = 0.f;
        }
    }

    // [Phase 2] 플레이어와 Sans 비활성화 및 Sans 이미지 변경 (2초 대기)
    if (imageChangedOnce && !deactivationDone)
    {
        afterTurnTimer += dt;
        if (afterTurnTimer >= 2.f)
        {
            player->SetActive(false);
            //sans->SetActive(false);
            sans->GetSprite().setTexture(TEXTURE_MGR.Get("Sprites/spr_sans_r_darkhand_2.png"));
            sf::Vector2u sansTexSize = sans->GetSprite().getTexture()->getSize();
            sans->GetSprite().setTextureRect(sf::IntRect(0, 0, sansTexSize.x, sansTexSize.y));
            deactivationDone = true; // 비활성화 완료 플래그
            reactivateTimer = 0.f;
        }
    }

    // [Phase 3] 플레이어와 Sans 재활성화 (추가 2초 대기)
    if (deactivationDone && !reactivated)
    {
        reactivateTimer += dt;
        if (reactivateTimer >= 2.f)
        {
            player->SetActive(true);
            sans->SetActive(true);
            sans->GetSprite().setTexture(TEXTURE_MGR.Get("Sprites/spr_sans_r_0.png"));
            sf::Vector2u sansTexSize = sans->GetSprite().getTexture()->getSize();
            sans->GetSprite().setTextureRect(sf::IntRect(0, 0, sansTexSize.x, sansTexSize.y));
            reactivated = true;
            // Sans 두번째 대화 시작을 위한 준비
            reactivateTimer = 0.f;
            sansSecondInteractTimer = 0.f;
            isWaitingSansSecondInteract = true;
        }
    }

    if (isWaitingSansSecondInteract)
    {
        sansSecondInteractTimer += dt;
        if (sansSecondInteractTimer >= 2.f)
        {
            player->SansSecondsInteract();
            isWaitingSansSecondInteract = false;
            isCheck = true;
        }
    }

    if (isCheck)
    {
        if (!dialoguebox->GetActive())
        {
            wallDisabled = true;
            isCheck = false;
        }
    }

    if (wallDisabled)
    {
        player->SetMove(true);
        player->animator.Play("Animation/idle.csv");
        isBattleInetrected = true;
        doorwall.setSize({ 0.f, 0.f });
        doorwall.setPosition({ -1000.f, -1000.f });
        wallDisabled = false;
    }
}
else
{
    // 벽에서 떨어지면 다시 움직일 수 있게
    player->SetMove(true);
}
	Scene::Update(dt);
}

void Map2::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.setView(worldView);
	window.draw(doorwall);

	if (Variables::isDrawHitBox)
	{
		for (auto& hit : hitboxes)
		{
			window.draw(*hit.shape); // worldView 기준으로 그려짐
		}
	}
}
