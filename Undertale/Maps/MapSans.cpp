#include "stdafx.h"
#include "MapSans.h"
#include "Player.h"
#include "SceneBattle.h"

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
	fontIds.push_back("fonts/DungGeunMo.ttf");
	soundIds.push_back("sounds/snd_txtsans.wav");

	ANI_CLIP_MGR.Load("Animation/idle.csv");
	ANI_CLIP_MGR.Load("Animation/downwalking.csv");
	ANI_CLIP_MGR.Load("Animation/upwalking.csv");
	ANI_CLIP_MGR.Load("Animation/leftwalking.csv");
	ANI_CLIP_MGR.Load("Animation/rightwalking.csv");

	player = (Player*)AddGameObject(new Player("Sprites/idle.png"));
	background = (SpriteGo*)AddGameObject(new SpriteGo());
	background->sortingLayer = SortingLayers::Background;
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
	lineCount = sansLines.size();
}

void MapSans::Enter()
{
	std::ifstream in("map7.json");
	if (!in)
	{
		std::cerr << "map7.json 파일을 열 수 없습니다!" << std::endl;
		return;
	}

	nlohmann::json j;
	in >> j;
	auto& mapData = j["map7"];

	// 배경
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
	uiView.setSize(size * 0.4f);
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

		rect->setOutlineThickness(1.f);
		hitboxes.push_back({ rect, typeStr });
	}

	//
	player->SetColorBlack();
	player->isSansMap = true;
	player->SetPosition(player->GetPosition() + sf::Vector2f(0.f, 8.f));
	SetColumn();

	sans.setTexture(TEXTURE_MGR.Get("graphics/spr_sans_l_dark_0.png"));
	Utils::SetOrigin(sans, Origins::MC);
	sans.setPosition({ 702.f,287.934f });

	isSansEvent = false;
	isSansTalking = false;

	textWindow.setTexture(TEXTURE_MGR.Get("Sprites/TextWindow.png"));
	textWindow.setScale(0.395f, 0.4f);
	Utils::SetOrigin(textWindow, Origins::TC);

	text.setFont(FONT_MGR.Get("fonts/DungGeunMo.ttf"));
	text.setCharacterSize(100); 
	text.setScale(0.12f, 0.12f); 
	lineIndex = 0;

	maxY = player->GetPosition().y;

	// 지우기
	PlayerInfo::PlusExp(99999);
	//
	if (PlayerInfo::lv == 20)
		IsSansDie = true;

	if (IsSansDie)
	{
		player->SetPosition({ 500.f, player->GetPosition().y });
	}
}

void MapSans::Update(float dt)
{
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
					SCENE_MGR.ChangeScene(SceneIds::Battle);
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
					if(tempLine[charIndex - 1] != L' ')
						SOUND_MGR.PlaySfx("sounds/snd_txtsans.wav");
				}
			}
		}
	}
	else
	{
		worldView.setCenter(player->GetPosition() + sf::Vector2f(0.f,-25.f));
		uiView.setCenter(player->GetPosition());
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
					std::cout << "씬 전환 트리거됨!" << std::endl;
					SCENE_MGR.ChangeScene(SceneIds::Dev1);
				}
				else if (hit.type == "NextScene")
				{
					std::cout << "NextScene" << std::endl;
					SCENE_MGR.ChangeScene(SceneIds::Ending);
				}
				else if (hit.type == "PrevScene")
				{
					std::cout << "PrevScene" << std::endl;
					SCENE_MGR.ChangeScene(SceneIds::MapPapyrus);
				}
			}
		}
		Scene::Update(dt);
	}	

	if (!IsSansDie && !isSansEvent && player->GetPosition().x >= 530.7)
	{
		timer = 0.f;
		isSansEvent = true;
		player->SetAnimatorStop();
	}

	if ((player->GetPosition().x <= -300.f || player->GetPosition().x >= 900.f) && player->GetPosition().y <= maxY)
	{
		player->isSansMap = false;
	}
	else if(player->GetPosition().y >= maxY)
	{
		player->isSansMap = true;
		player->SetPosition({ player->GetPosition().x,maxY });
	}

	// 테스트 코드
	if (InputMgr::GetKeyDown(sf::Keyboard::Numpad5))
	{
		player->SetPosition({ 500.f, player->GetPosition().y });
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Numpad6))
	{
		SceneBattle::nextSceneId = SceneIds::MapSans;
		SceneBattle::monsterJsonID = "jsons/sans.json";
		player->StartBattle();
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Numpad7))
	{
		std::cout << player->GetPosition().x << ", " << player->GetPosition().y << std::endl;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Numpad8))
	{
		SCENE_MGR.ChangeScene(SceneIds::Ending);
	}
}

void MapSans::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	if(!IsSansDie)
		window.draw(sans);
	window.setView(worldView);

	if (Variables::isDrawHitBox)
	{
		for (auto& hit : hitboxes)
		{
			window.draw(*hit.shape); // worldView 기준으로 그려짐
		}
	}

	window.setView(uiView);
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

