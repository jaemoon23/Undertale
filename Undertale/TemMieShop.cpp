#include "stdafx.h"
#include "TemMieShop.h"
#include "SpriteGo.h"
#include "TextGo.h"

TemMieShop::TemMieShop() : Scene(SceneIds::TemMieShop)
{
}

void TemMieShop::Init()
{
	fontIds.push_back("fonts/DungGeunMo.ttf");
	texIds.push_back("Sprites/TemMieShop/TemMie_Shop.png");
	texIds.push_back("Sprites/TemMieShop/TemMieBody.png");
	texIds.push_back("Sprites/TemMieShop/TemMieBox.png");
	texIds.push_back("Sprites/TemMieShop/TemMieShopTextWindow.png");
	texIds.push_back("Sprites/TemMieShop/Selection_Icon.png");

	SOUNDBUFFER_MGR.Load("sounds/TemMie/44 Tem Shop.flac");
	SOUNDBUFFER_MGR.Load("sounds/TemMie/temText.wav");
	SOUNDBUFFER_MGR.Load("sounds/TemMie/temText2.wav");
	SOUNDBUFFER_MGR.Load("sounds/TemMie/temText3.wav");
	SOUNDBUFFER_MGR.Load("sounds/TemMie/temText4.wav");

	backGround = (SpriteGo*)AddGameObject(new SpriteGo("Sprites/TemMieShop/TemMie_Shop.png"));
	temMieBody = (SpriteGo*)AddGameObject(new SpriteGo("Sprites/TemMieShop/TemMieBody.png"));
	temShopBox = (SpriteGo*)AddGameObject(new SpriteGo("Sprites/TemMieShop/TemMieBox.png"));
	temShopTextWindow = (SpriteGo*)AddGameObject(new SpriteGo("Sprites/TemMieShop/TemMieShopTextWindow.png"));
	temShopItemWindow = (SpriteGo*)AddGameObject(new SpriteGo("Sprites/TemMieShop/TemMieShopTextWindow.png"));
	Selection_Icon = (SpriteGo*)AddGameObject(new SpriteGo("Sprites/TemMieShop/Selection_Icon.png"));

	introText = (TextGo*)AddGameObject(new TextGo("fonts/DungGeunMo.ttf"));
	buyText = (TextGo*)AddGameObject(new TextGo("fonts/DungGeunMo.ttf"));
	sellText = (TextGo*)AddGameObject(new TextGo("fonts/DungGeunMo.ttf"));
	exitText = (TextGo*)AddGameObject(new TextGo("fonts/DungGeunMo.ttf"));
	goldText = (TextGo*)AddGameObject(new TextGo("fonts/DungGeunMo.ttf"));
	slotText = (TextGo*)AddGameObject(new TextGo("fonts/DungGeunMo.ttf"));

	Scene::Init();
}

void TemMieShop::Enter()
{
	SOUND_MGR.PlayBgm("sounds/TemMie/44 Tem Shop.flac");
	backGround->sortingLayer = SortingLayers::Background;
	backGround->sortingOrder = 0;

	temShopBox->sortingLayer = SortingLayers::Foreground;
	temShopBox->sortingOrder = 1;
	temShopBox->SetOrigin(Origins::MC);
	temShopBox->SetPosition({ 150.f,95.f });

	temMieBody->sortingLayer = SortingLayers::Foreground;
	temMieBody->sortingOrder = 1;
	temMieBody->SetOrigin(Origins::MC);
	temMieBody->SetPosition({ temShopBox->GetPosition().x + 5.f, temShopBox->GetPosition().y - 50.f });

	temShopTextWindow->sortingLayer = SortingLayers::UI;
	temShopTextWindow->sortingOrder = 0;
	temShopTextWindow->SetOrigin(Origins::TL);
	temShopTextWindow->SetScale({ 0.74f,0.8f });
	temShopTextWindow->SetPosition({ 0.f, 240.f });

	temShopItemWindow->sortingLayer = SortingLayers::UI;
	temShopItemWindow->sortingOrder = 0;
	temShopItemWindow->SetOrigin(Origins::TL);
	temShopItemWindow->SetScale({ 0.52f,0.8f });
	temShopItemWindow->SetPosition({ 0.f, 240.f });

	fullText = L"* 안뇽!\n* 테미 샵에 온 걸...\n* 화녕행!!!!";
	currentText = L"";
	currentIndex = 0;
	textTimer = 0.f;

	introText->SetCharacterSize(30.f);
	introText->sortingLayer = SortingLayers::UI;
	introText->sortingOrder = 1;

	buyText->SetString(L"산다");
	buyText->SetCharacterSize(30.f);
	buyText->sortingLayer = SortingLayers::UI;
	buyText->sortingOrder = 1;
	buyText->SetPosition({ temShopTextWindow->GetPosition().x + 490.f, temShopTextWindow->GetPosition().y + 25.f });

	sellText->SetString(L"판다");
	sellText->SetCharacterSize(30.f);
	sellText->sortingLayer = SortingLayers::UI;
	sellText->sortingOrder = 1;
	sellText->SetPosition({ temShopTextWindow->GetPosition().x + 490.f, temShopTextWindow->GetPosition().y + 75.f });

	exitText->SetString(L"나가기");
	exitText->SetCharacterSize(30.f);
	exitText->sortingLayer = SortingLayers::UI;
	exitText->sortingOrder = 1;
	exitText->SetPosition({ temShopTextWindow->GetPosition().x + 490.f, temShopTextWindow->GetPosition().y + 125.f });

	gold = PlayerInfo::gold;
	goldText->SetString("(" + std::to_string(gold) + "G)");
	goldText->SetFillColor(sf::Color::Yellow);
	goldText->SetCharacterSize(20.f);
	goldText->sortingLayer = SortingLayers::UI;
	goldText->sortingOrder = 1;
	goldText->SetPosition({ temShopTextWindow->GetPosition().x + 470.f, temShopTextWindow->GetPosition().y + 175.f });

	slot = 0;
	slotText->SetString(std::to_string(slot) + "/4");
	slotText->SetCharacterSize(20.f);
	slotText->sortingLayer = SortingLayers::UI;
	slotText->sortingOrder = 1;
	slotText->SetPosition({ temShopTextWindow->GetPosition().x + 570.f, temShopTextWindow->GetPosition().y + 175.f });

	Selection_Icon->sortingLayer = SortingLayers::UI;
	Selection_Icon->sortingOrder = 1;
	Selection_Icon->SetPosition({ sellText->GetPosition().x + -25.f, temShopTextWindow->GetPosition().y + 40.f });

	Selection_Icon_HitBox.setSize({ 16.f,16.f });
	Selection_Icon_HitBox.setFillColor(sf::Color::Transparent);
	Selection_Icon_HitBox.setOutlineColor(sf::Color::Green);
	Selection_Icon_HitBox.setOutlineThickness(1.f);
	Selection_Icon_HitBox.setPosition(Selection_Icon->GetPosition());

	sellText_HitBox.setSize({ 80.f,30.f });
	sellText_HitBox.setFillColor(sf::Color::Transparent);
	sellText_HitBox.setOutlineColor(sf::Color::Green);
	sellText_HitBox.setOutlineThickness(1.f);
	sellText_HitBox.setPosition({ sellText->GetPosition().x - 20.f, sellText->GetPosition().y + 5.f });

	buyText_HitBox.setSize({ 80.f,30.f });
	buyText_HitBox.setFillColor(sf::Color::Transparent);
	buyText_HitBox.setOutlineColor(sf::Color::Green);
	buyText_HitBox.setOutlineThickness(1.f);
	buyText_HitBox.setPosition({ buyText->GetPosition().x - 20.f, buyText->GetPosition().y + 5.f });

	exitText_HitBox.setSize({ 110.f,30.f });
	exitText_HitBox.setFillColor(sf::Color::Transparent);
	exitText_HitBox.setOutlineColor(sf::Color::Green);
	exitText_HitBox.setOutlineThickness(1.f);
	exitText_HitBox.setPosition({ exitText->GetPosition().x - 20.f, exitText->GetPosition().y + 5.f });

	Scene::Enter();
	
	sf::Vector2f size = { 640.f, 480.f };
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	worldView.setSize(size * 0.5f);
	worldView.setCenter({ backGround->GetLocalBounds().width * 0.5f, backGround->GetLocalBounds().height * 0.5f });
	uiView.setSize(size);
	uiView.setCenter(center);
	
}

void TemMieShop::Update(float dt)
{
	// 인트로 텍스트
	if (isIntroText)
	{
		textTimer += dt;

		if (currentIndex >= fullText.size())
		{
			isIntroText = false; // 다음 메뉴에서 나가기 누를때마다 트루 시켜주기
		}
		else if (textTimer >= textSpeed) // 글자 출력 간격 도달했으면 다음 글자 추가
		{
			SOUND_MGR.PlaySfx("sounds/TemMie/temText.wav");

			textTimer = 0.f;
			currentText += fullText[currentIndex];
			currentIndex++;

			introText->SetString(currentText); // 실제 텍스트 객체에 반영
			introText->SetPosition({ temShopTextWindow->GetPosition().x + 30.f, temShopTextWindow->GetPosition().y + 25.f });
		}
	}
	// 선택 아이콘
	if (InputMgr::GetKeyDown(sf::Keyboard::Up))
	{
		if (!(textCount <= 0))
		{
			textCount--;
			textPos -= 50.f;
		}
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Down))
	{
		if (!(textCount >= 2))
		{
			textCount++;
			textPos += 50.f;
		}
	}

	Selection_Icon->SetPosition({ sellText->GetPosition().x + -25.f, temShopTextWindow->GetPosition().y + 40.f + textPos });
	Selection_Icon_HitBox.setPosition(Selection_Icon->GetPosition());

	if (InputMgr::GetKeyDown(sf::Keyboard::Z))
	{
		if (Utils::CheckCollision(Selection_Icon_HitBox, buyText_HitBox))
		{
			std::cout << "산다" << std::endl;
		}
		else if (Utils::CheckCollision(Selection_Icon_HitBox, sellText_HitBox))
		{
			std::cout << "판다" << std::endl;
		}
		else if (Utils::CheckCollision(Selection_Icon_HitBox, exitText_HitBox))
		{
			std::cout << "나가기" << std::endl;
		}
	}
	Scene::Update(dt);
}

void TemMieShop::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

	if (Variables::isDrawHitBox)
	{
		window.draw(Selection_Icon_HitBox);
		window.draw(exitText_HitBox);
		window.draw(buyText_HitBox);
		window.draw(sellText_HitBox);
	}
	
}


