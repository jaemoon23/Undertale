#include "stdafx.h"
#include "MapSans.h"
#include "Player.h"
#include "SceneBattle.h"
#include "DialogueBox.h"
#include "UiChanger.h"
#include "InventoryUi.h"
#include "PlayerInfoUi.h"

MapSans::MapSans() : Scene(SceneIds::MapSans)
{
}

void MapSans::Init()
{
	texIds.push_back("graphics/spr_sans_bface_0.png");
	texIds.push_back("graphics/spr_sans_bface_1.png");
	texIds.push_back("graphics/spr_sans_bface_2.png");
	texIds.push_back("graphics/spr_sans_bface_3.png");
	texIds.push_back("graphics/spr_sans_bface_4.png");
	texIds.push_back("graphics/spr_sans_bface_5.png");
	texIds.push_back("graphics/spr_sans_bface_7.png");
	texIds.push_back("graphics/spr_sans_bface_8.png");
	texIds.push_back("graphics/spr_sans_bface_9.png");
	texIds.push_back("Sprites/TextWindow.png");
	texIds.push_back("graphics/spr_sans_l_dark_0.png");
	texIds.push_back("graphics/column.png");
	texIds.push_back("Sprites/idle.png");
	texIds.push_back("graphics/SansBack.png");
	texIds.push_back("Sprites/downwalking.png");
	texIds.push_back("Sprites/upwalking.png");
	texIds.push_back("Sprites/leftwalking.png");
	texIds.push_back("Sprites/rightwalking.png");
	texIds.push_back("Sprites/spr_heart_battle_pl_0.png");
	texIds.push_back("Sprites/backgroundui.png");
	fontIds.push_back("fonts/DungGeunMo.ttf");
	soundIds.push_back("sounds/snd_escaped.wav");
	soundIds.push_back("sounds/snd_txtsans.wav");
	soundIds.push_back("sounds/73 The Choice.flac");
	
	ANI_CLIP_MGR.Load("Animation/idle.csv");
	ANI_CLIP_MGR.Load("Animation/downwalking.csv");
	ANI_CLIP_MGR.Load("Animation/upwalking.csv");
	ANI_CLIP_MGR.Load("Animation/leftwalking.csv");
	ANI_CLIP_MGR.Load("Animation/rightwalking.csv");

	SOUNDBUFFER_MGR.Load("sounds/snd_select.wav");

	player = (Player*)AddGameObject(new Player("Sprites/idle.png"));
	background = (SpriteGo*)AddGameObject(new SpriteGo());
	background->sortingLayer = SortingLayers::Background;

	InventoryInit();

	Scene::Init();

	sansLines = {
		L"* 안녕",
		L"* 꽤 바빴었지, 응?",
		L"* ...",
		L"* 그래, 물어볼 게\n  하나 있어",
		L"* 가장 나쁜 사람이라도\n  바뀔 수 있을까...?",
		L"* 노력만 한다면,\n  모두가 착한 사람이\n  될 수 있을까?",
		L"* 헤 헤 헤 헤...",
		L"* 좋아.",
		L"* 뭐, 여기 더 괜찮은\n  질문이 있어.",
		L"* 끔찍한 시간을\n  보내고 싶어?"
	};
	sansFaceIds = {
		"graphics/spr_sans_bface_0.png",
		"graphics/spr_sans_bface_1.png",
		"graphics/spr_sans_bface_1.png",
		"graphics/spr_sans_bface_0.png",
		"graphics/spr_sans_bface_4.png",
		"graphics/spr_sans_bface_4.png",
		"graphics/spr_sans_bface_4.png",
		"graphics/spr_sans_bface_1.png",
		"graphics/spr_sans_bface_4.png",
		"graphics/spr_sans_bface_5.png"
	};

	sansPeacefulLines = {
		L"* 드디어 왔네.",
		L"* 네 여정의 끝이\n  코 앞이야.",
		L"* 지금까지 수고했어.",
		L"* 네가 보여준 친절을\n  기억할게.",
		L"* 안녕 작은 꼬마 친구."
	};
	sansPeacefulFaceIds = {
		"graphics/spr_sans_bface_1.png",
		"graphics/spr_sans_bface_0.png",
		"graphics/spr_sans_bface_7.png",
		"graphics/spr_sans_bface_0.png",
		"graphics/spr_sans_bface_9.png"
	};

	lineCount = sansLines.size();
	peacefullLineCount = sansPeacefulLines.size();
}

void MapSans::Enter()
{
	Scene::LoadMapFromJson("map7.json", "map7", player, background, objects, hitboxes);
	
	Scene::Enter();

	sf::Vector2f size = { 640.f, 480.f };
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	worldView.setSize(size * 0.5f);
	uiView.setSize(size * 0.4f);
	uiView.setCenter(center);

	//
	player->SetColorBlack();
	player->isSansMap = true;
	player->SetPosition(player->GetPosition() + sf::Vector2f(0.f, 8.f));
	SetColumn();

	sans.setTexture(TEXTURE_MGR.Get("graphics/spr_sans_l_dark_0.png"));
	Utils::SetOrigin(sans, Origins::MC);
	sans.setPosition({ 702.f,295.934f });

	isSansEvent = false;
	isSansTalking = false;
	isEnd = false;
	isBattleEnter = false;

	textWindow.setTexture(TEXTURE_MGR.Get("Sprites/TextWindow.png"));
	textWindow.setScale(0.395f, 0.4f);
	Utils::SetOrigin(textWindow, Origins::TC);

	text.setFont(FONT_MGR.Get("fonts/DungGeunMo.ttf"));
	text.setCharacterSize(100);
	text.setScale(0.12f, 0.12f);
	lineIndex = 0;

	maxY = player->GetPosition().y;

	if (PlayerInfo::lv == 20)
		IsSansDie = true;

	SOUND_MGR.PlayBgm("sounds/73 The Choice.flac");

	player->SetPosition(startPos);
}

void MapSans::Update(float dt)
{
	if (isBattleEnter)
	{
		player->Update(dt);
		return;
	}

	if (isSansEvent)
	{
		timer += dt;
		if (timer >= waitingTime && timer <= waitingTime + screenMoveTime)
		{
			sf::Vector2f worldViewCenter = worldView.getCenter();
			sf::Vector2f uiViewCenter = uiView.getCenter();
			worldViewCenter.x += 80.f / screenMoveTime * dt;
			uiViewCenter.x += 136.f / screenMoveTime * dt;
			worldView.setCenter(worldViewCenter);
			uiView.setCenter(uiViewCenter);
		}
		else if (timer > waitingTime + screenMoveTime)
		{
			isSansTalking = true;
			textWindow.setPosition(uiView.getCenter() + sf::Vector2f(0.f, -93.f));
			sansFace.setPosition(uiView.getCenter() + sf::Vector2f(-100.f, -78.f));
			text.setPosition(uiView.getCenter() + sf::Vector2f(-58.f, -87.f));
		}

		if (isSansTalking)
		{
			if (PlayerInfo::Moral < JudgeMentPoint)
			{
				if (lineIndex == 0)
				{
					isDrawingText = true;
					charIndex = 0;
					typeTimer = 0.f;
					tempLine = sansLines[lineIndex];
					sansFace.setTexture(TEXTURE_MGR.Get(sansFaceIds[lineIndex++]));
				}

				if (InputMgr::GetKeyDown(sf::Keyboard::Z))
				{
					if (lineIndex == lineCount)
					{
						SceneBattle::nextSceneId = SceneIds::MapSans;
						SceneBattle::monsterJsonID = "jsons/sans.json";
						isBattleEnter = true;
						player->StartBattle();
						startPos = player->GetPosition() + sf::Vector2f(-20.f, 0.f);
						return;
					}
					isDrawingText = true;
					charIndex = 0;
					typeTimer = 0.f;
					tempLine = sansLines[lineIndex];
					sansFace.setTexture(TEXTURE_MGR.Get(sansFaceIds[lineIndex++]));
				}

				if (isDrawingText)
				{
					typeTimer += dt;
					if (charIndex < tempLine.size() && typeTimer > typeTime)
					{
						typeTimer = 0.f;
						charIndex++;
						currentLine = tempLine.substr(0, charIndex);
						text.setString(currentLine);
						if (tempLine[charIndex - 1] != L' ')
							SOUND_MGR.PlaySfx("sounds/snd_txtsans.wav");
					}
				}
			}
			else
			{
				if (peacefullLineIndex == 0)
				{
					isDrawingText = true;
					charIndex = 0;
					typeTimer = 0.f;
					tempLine = sansPeacefulLines[peacefullLineIndex];
					sansFace.setTexture(TEXTURE_MGR.Get(sansPeacefulFaceIds[peacefullLineIndex++]));
				}

				if (InputMgr::GetKeyDown(sf::Keyboard::Z))
				{
					if (peacefullLineIndex == peacefullLineCount)
					{
						isSansEvent = false;
						isSansTalking = false;
						isTalkEnd = true;
						return;
					}
					isDrawingText = true;
					charIndex = 0;
					typeTimer = 0.f;
					tempLine = sansPeacefulLines[peacefullLineIndex];
					sansFace.setTexture(TEXTURE_MGR.Get(sansPeacefulFaceIds[peacefullLineIndex++]));
				}

				if (isDrawingText)
				{
					typeTimer += dt;
					if (charIndex < tempLine.size() && typeTimer > typeTime)
					{
						typeTimer = 0.f;
						charIndex++;
						currentLine = tempLine.substr(0, charIndex);
						text.setString(currentLine);
						if (tempLine[charIndex - 1] != L' ')
							SOUND_MGR.PlaySfx("sounds/snd_txtsans.wav");
					}
				}
			}
		}
	}
	else
	{
		worldView.setCenter(player->GetPosition() + sf::Vector2f(0.f, -25.f));
		uiView.setCenter(player->GetPosition());
		battleCheckTimer += dt;
		if (InputMgr::GetKeyDown(sf::Keyboard::Return))
		{
			std::cout << player->GetPosition().x << ", " << player->GetPosition().y << std::endl;
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
					SCENE_MGR.ChangeScene(SceneIds::Dev1);
				}
				else if (hit.type == "NextScene")
				{
					if(!isEnd)
						SOUND_MGR.PlaySfx("sounds/snd_escaped.wav");
					isEnd = true;
				}
				else if (hit.type == "PrevScene")
				{
					std::cout << "PrevScene" << std::endl;
					startPos = { -328.f,295.934f };
					SCENE_MGR.ChangeScene(SceneIds::MapPapyrus);
				}
			}
		}

		if (!isEnd)
			Scene::Update(dt);
	}

	if (isEnd)
	{
		endTimer += dt;
		sf::Vector2f playerPos = player->GetPosition();
		playerPos.y -= 20.f / endTime * dt;
		player->SetPosition(playerPos);
		if (endTimer >= endTime)
		{
			SCENE_MGR.ChangeScene(SceneIds::Ending);
		}
	}

	if (!isTalkEnd && !IsSansDie && !isSansEvent && player->GetPosition().x >= 530.7)
	{
		timer = 0.f;
		isSansEvent = true;
		player->SetAnimatorStop();
	}

	if ((player->GetPosition().x <= -300.f || player->GetPosition().x >= 900.f) && player->GetPosition().y <= maxY)
	{
		player->isSansMap = false;
	}
	else if (player->GetPosition().y >= maxY)
	{
		player->isSansMap = true;
		player->SetPosition({ player->GetPosition().x,maxY });
	}

	uiViewCenter = uiView.getCenter();
}

void MapSans::Draw(sf::RenderWindow& window)
{
	sf::Vector2f size = { 640.f, 480.f };
	uiView.setSize(size);
	uiView.setCenter({ 320.f,240.f });
	Scene::Draw(window);
	uiView.setSize(size * 0.4f);
	uiView.setCenter(uiViewCenter);
	window.setView(worldView);
	if (!IsSansDie)
		window.draw(sans);

	if (Variables::isDrawHitBox)
	{
		for (auto& hit : hitboxes)
		{
			window.draw(*hit.shape);
		}
	}

	window.setView(uiView);
	if (!isBattleEnter)
	{
		for (int i = 0; i < columnCount; ++i)
		{
			window.draw(column[i]);
		}
		if (isSansTalking)
		{
			window.draw(textWindow);
			window.draw(sansFace);
			window.draw(text);
		}
	}	
}

void MapSans::SetColumn()
{
	column.clear();

	for (int i = 0; i < columnCount - 3; ++i)
	{
		sf::Sprite bg;
		bg.setTexture(TEXTURE_MGR.Get("graphics/column.png"));
		Utils::SetOrigin(bg, Origins::BC);
		sf::Vector2f pos = player->GetPosition();
		pos.x += 70.f;
		pos.x += i * 180.f;
		pos.y += 67.0f;
		bg.setPosition(pos);
		column.push_back(bg);
	}
	for (int i = 0; i < 2; ++i)
	{
		sf::Sprite bg;
		bg.setTexture(TEXTURE_MGR.Get("graphics/column.png"));
		Utils::SetOrigin(bg, Origins::BC);
		sf::Vector2f pos = column[columnCount - 4].getPosition();
		pos.x += (i + 1) * 100.f;
		bg.setPosition(pos);
		column.push_back(bg);
	}
	sf::Sprite bg;
	bg.setTexture(TEXTURE_MGR.Get("graphics/column.png"));
	Utils::SetOrigin(bg, Origins::BC);
	sf::Vector2f pos = column[columnCount - 2].getPosition();
	pos.x += 180.f;
	bg.setPosition(pos);
	column.push_back(bg);
}

void MapSans::InventoryInit()
{
	inventoryui = (InventoryUi*)AddGameObject(new InventoryUi("InventoryUi"));
	dialoguebox = (DialogueBox*)AddGameObject(new DialogueBox("dialoguebox"));
	uichanger = (UiChanger*)AddGameObject(new UiChanger("uichanger"));
	playerinfoui = (PlayerInfoUi*)AddGameObject(new PlayerInfoUi("playerinfoui"));

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
}

