#include "stdafx.h"
#include "TemMieShop.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "TemMieBody.h"

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

	texIds.push_back("Sprites/temmie/spr_5_tembody.png");
	texIds.push_back("Sprites/temmie/Tembody1.png");
	texIds.push_back("Sprites/TemMieShop/TemMieBody.png");
	
	ANI_CLIP_MGR.Load("Animation/temmie/Temmie_smiling.csv");
	ANI_CLIP_MGR.Load("Animation/temmie/Temmie_shop_Idle.csv");

	SOUNDBUFFER_MGR.Load("sounds/TemMie/44 Tem Shop.flac");
	SOUNDBUFFER_MGR.Load("sounds/TemMie/temText.wav");
	SOUNDBUFFER_MGR.Load("sounds/TemMie/temText2.wav");
	SOUNDBUFFER_MGR.Load("sounds/TemMie/temText3.wav");
	SOUNDBUFFER_MGR.Load("sounds/TemMie/temText4.wav");
	SOUNDBUFFER_MGR.Load("sounds/TemMie/BuyItem.wav");

	backGround = (SpriteGo*)AddGameObject(new SpriteGo("Sprites/TemMieShop/TemMie_Shop.png"));

	temMieBody = (TemMieBody*)AddGameObject(new TemMieBody("Sprites/temmie/spr_5_tembody.png"));

	temShopBox = (SpriteGo*)AddGameObject(new SpriteGo("Sprites/TemMieShop/TemMieBox.png"));
	temShopTextWindow = (SpriteGo*)AddGameObject(new SpriteGo("Sprites/TemMieShop/TemMieShopTextWindow.png"));
	temShopItemWindow = (SpriteGo*)AddGameObject(new SpriteGo("Sprites/TemMieShop/TemMieShopTextWindow.png"));
	Selection_Icon = (SpriteGo*)AddGameObject(new SpriteGo("Sprites/TemMieShop/Selection_Icon.png"));
	Buy_Selection_Icon = (SpriteGo*)AddGameObject(new SpriteGo("Sprites/TemMieShop/Selection_Icon.png"));

	introText = (TextGo*)AddGameObject(new TextGo("fonts/DungGeunMo.ttf"));
	buyText = (TextGo*)AddGameObject(new TextGo("fonts/DungGeunMo.ttf"));
	sellText = (TextGo*)AddGameObject(new TextGo("fonts/DungGeunMo.ttf"));
	exitText = (TextGo*)AddGameObject(new TextGo("fonts/DungGeunMo.ttf"));
	goldText = (TextGo*)AddGameObject(new TextGo("fonts/DungGeunMo.ttf"));
	slotText = (TextGo*)AddGameObject(new TextGo("fonts/DungGeunMo.ttf"));
	iceText = (TextGo*)AddGameObject(new TextGo("fonts/DungGeunMo.ttf"));
	snowManText = (TextGo*)AddGameObject(new TextGo("fonts/DungGeunMo.ttf"));
	cookieText = (TextGo*)AddGameObject(new TextGo("fonts/DungGeunMo.ttf"));
	Scene::Init();
}

void TemMieShop::Enter()
{
	
	Scene::Enter();
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
	temShopItemWindow->SetActive(true);

	introText->SetString("");
	introText->SetCharacterSize(30.f);
	introText->sortingLayer = SortingLayers::UI;
	introText->sortingOrder = 1;

	buyText->SetString(L"산다");
	buyText->SetCharacterSize(30.f);
	buyText->sortingLayer = SortingLayers::UI;
	buyText->sortingOrder = 1;
	buyText->SetPosition({ temShopTextWindow->GetPosition().x + 490.f, temShopTextWindow->GetPosition().y + 25.f });
	buyText->SetActive(true);
	
	sellText->SetString(L"판다");
	sellText->SetCharacterSize(30.f);
	sellText->sortingLayer = SortingLayers::UI;
	sellText->sortingOrder = 1;
	sellText->SetPosition({ temShopTextWindow->GetPosition().x + 490.f, temShopTextWindow->GetPosition().y + 75.f });
	sellText->SetActive(true);

	exitText->SetString(L"나가기");
	exitText->SetCharacterSize(30.f);
	exitText->sortingLayer = SortingLayers::UI;
	exitText->sortingOrder = 1;
	exitText->SetPosition({ temShopTextWindow->GetPosition().x + 490.f, temShopTextWindow->GetPosition().y + 125.f });
	exitText->SetActive(true);

	goldText->SetString("(" + std::to_string(PlayerInfo::gold) + "G)");
	goldText->SetFillColor(sf::Color::Yellow);
	goldText->SetCharacterSize(20.f);
	goldText->sortingLayer = SortingLayers::UI;
	goldText->sortingOrder = 1;
	goldText->SetPosition({ temShopTextWindow->GetPosition().x + 470.f, temShopTextWindow->GetPosition().y + 175.f });

	slotText->SetString(std::to_string(PlayerInfo::slot) + "/4");
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

	// 구매창
	snowManText->SetString(L"눈사람");
	snowManText->SetCharacterSize(30.f);
	snowManText->sortingLayer = SortingLayers::UI;
	snowManText->sortingOrder = 1;
	snowManText->SetPosition({ temShopTextWindow->GetPosition().x + 50.f, temShopTextWindow->GetPosition().y + 25.f });
	snowManText->SetActive(false);

	cookieText->SetString(L"쿠키");
	cookieText->SetCharacterSize(30.f);
	cookieText->sortingLayer = SortingLayers::UI;
	cookieText->sortingOrder = 1;
	cookieText->SetPosition({ temShopTextWindow->GetPosition().x + 50.f, temShopTextWindow->GetPosition().y + 75.f });
	cookieText->SetActive(false);

	iceText->SetString(L"아이스크림");
	iceText->SetCharacterSize(30.f);
	iceText->sortingLayer = SortingLayers::UI;
	iceText->sortingOrder = 1;
	iceText->SetPosition({ temShopTextWindow->GetPosition().x + 50.f, temShopTextWindow->GetPosition().y + 125.f });
	iceText->SetActive(false);
	
	
	Buy_Selection_Icon->sortingLayer = SortingLayers::UI;
	Buy_Selection_Icon->sortingOrder = 1;
	Buy_Selection_Icon->SetPosition({ snowManText->GetPosition().x + -25.f, snowManText->GetPosition().y + 20.f });
	Buy_Selection_Icon->SetActive(false);

	Buy_Selection_Icon_HitBox.setSize({ 16.f,16.f });
	Buy_Selection_Icon_HitBox.setFillColor(sf::Color::Transparent);
	Buy_Selection_Icon_HitBox.setOutlineColor(sf::Color::Green);
	Buy_Selection_Icon_HitBox.setOutlineThickness(1.f);
	Buy_Selection_Icon_HitBox.setPosition(Buy_Selection_Icon->GetPosition());

	SnowManText_HitBox.setSize({ 80.f,30.f });
	SnowManText_HitBox.setFillColor(sf::Color::Transparent);
	SnowManText_HitBox.setOutlineColor(sf::Color::Green);
	SnowManText_HitBox.setOutlineThickness(1.f);
	SnowManText_HitBox.setPosition({ snowManText->GetPosition().x - 20.f, snowManText->GetPosition().y + 5.f });

	CookieText_HitBox.setSize({ 80.f,30.f });
	CookieText_HitBox.setFillColor(sf::Color::Transparent);
	CookieText_HitBox.setOutlineColor(sf::Color::Green);
	CookieText_HitBox.setOutlineThickness(1.f);
	CookieText_HitBox.setPosition({ cookieText->GetPosition().x - 20.f, cookieText->GetPosition().y + 5.f });

	IceText_HitBox.setSize({ 110.f,30.f });
	IceText_HitBox.setFillColor(sf::Color::Transparent);
	IceText_HitBox.setOutlineColor(sf::Color::Green);
	IceText_HitBox.setOutlineThickness(1.f);
	IceText_HitBox.setPosition({ iceText->GetPosition().x - 20.f, iceText->GetPosition().y + 5.f });


	fullText = L"* 안뇽!\n* 테미 샵에 온 걸...\n* 화녕행!!!!";
	currentText = L"";

	textTimer = 0.f;
	textSpeed = 0.05f; // 글자당 시간 (초)
	currentIndex = 0;

	isIntro = true;
	isIntroText = true;
	menu = false;
	isMenuSelect = true;
	menuExit = false;
	isBuy = false;
	isSell = false;
	selectItem = false;
	sellItem = false;

	textCount = 0;
	textPos = 0.f;

	buyTextCount = 0;
	buyTextPos = 0.f;

	// 아이템 샵
	snowManPrice = 10; // 눈사람 가격
	cookiePrice = 15; // 쿠키 가격
	icePrice = 20; // 아이스 가격

	itemName = L"";

	sf::Vector2f size = { 640.f, 480.f };
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	worldView.setSize(size * 0.5f);
	worldView.setCenter({ backGround->GetLocalBounds().width * 0.5f, backGround->GetLocalBounds().height * 0.5f });
	uiView.setSize(size);
	uiView.setCenter(center);
	
}

void TemMieShop::Update(float dt)
{

	IntroText(dt);
	
	// 메뉴 선택
	if (menu)
	{
		
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
		
		

		if (InputMgr::GetKeyDown(sf::Keyboard::Z) && isMenuSelect)
		{
			if (Utils::CheckCollision(Selection_Icon_HitBox, buyText_HitBox))
			{
				// 인트로 오브젝트
				introText->SetActive(false);
				buyText->SetActive(false);
				sellText->SetActive(false);
				exitText->SetActive(false);
				Selection_Icon->SetActive(false);
				menuExit = true;

				// 구매 오브젝트
				snowManText->SetActive(true);
				cookieText->SetActive(true);
				iceText->SetActive(true);
				Buy_Selection_Icon->SetActive(true);

				currentText = L"";

				isBuy = true;
				isMenuSelect = false;
			}
			else if (Utils::CheckCollision(Selection_Icon_HitBox, sellText_HitBox))
			{
				introText->SetActive(false);
				buyText->SetActive(false);
				sellText->SetActive(false);
				exitText->SetActive(false);
				Selection_Icon->SetActive(false);

				snowManText->SetActive(true);
				cookieText->SetActive(true);
				iceText->SetActive(true);
				Buy_Selection_Icon->SetActive(true);
				isSell = true;
				menuExit = true;
				currentText = L"";
				isMenuSelect = false;
			}
			else if (Utils::CheckCollision(Selection_Icon_HitBox, exitText_HitBox))
			{
				isMenuSelect = false;
				SCENE_MGR.ChangeScene(SceneIds::Map4);
				
			}
		}

		// 돌아가기 로직
		if (menuExit)
		{
			if (InputMgr::GetKeyDown(sf::Keyboard::X))
			{
				// 인트로 오브젝트
				isMenuSelect = true;
				temShopItemWindow->SetActive(true);
				buyText->SetActive(true);
				sellText->SetActive(true);
				exitText->SetActive(true);
				Selection_Icon->SetActive(true);

				// 구매 오브젝트
				snowManText->SetActive(false);
				cookieText->SetActive(false);
				iceText->SetActive(false);
				Buy_Selection_Icon->SetActive(false);

				currentIndex = 0;
				textTimer = 0.f;
				isIntroText = true;
				menu = false;
				isBuy = false;
				isSell = false;
				IntroText(dt);
				menuExit = false;
				selectItem = false;
				sellItem = false;
			}
		}
	}

#pragma region 구매 시스템
	// 구매창
	if (isBuy)
	{
		// 선택 아이콘
		if (InputMgr::GetKeyDown(sf::Keyboard::Up))
		{
			selectItem = true;
			if (!(buyTextCount <= 0))
			{
				buyTextCount--;
				buyTextPos -= 50.f;
			}
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Down))
		{
			selectItem = true;
			if (!(textCount >= 2))
			{
				buyTextCount++;
				buyTextPos += 50.f;
			}
		}
		Buy_Selection_Icon->SetPosition({ snowManText->GetPosition().x + -25.f, snowManText->GetPosition().y + 15.f + textPos });
		Buy_Selection_Icon_HitBox.setPosition(Buy_Selection_Icon->GetPosition());

		if (InputMgr::GetKeyDown(sf::Keyboard::Z) && selectItem)
		{
			if (!(PlayerInfo::slot >= 4))
			{
				// 눈사람
				if (Utils::CheckCollision(Buy_Selection_Icon_HitBox, SnowManText_HitBox) && PlayerInfo::gold >= snowManPrice)
				{
					for (int i = 0; i < 4; ++i)
					{
						if (InventoryUi::healItem[i].GetName() == L"")
						{
							InventoryUi::healItem[i].SetInfo(L"눈사람", 5);
							std::cout << "눈사람 구매" << std::endl;
							PlayerInfo::slot++;
							PlayerInfo::gold -= snowManPrice;
							goldText->SetString("(" + std::to_string(PlayerInfo::gold) + "G)");
							SOUND_MGR.PlaySfx("sounds/TemMie/BuyItem.wav");
							// set함수
							temMieBody->SetSmiling(true);
							break;
						}
					}
				}
				else if (PlayerInfo::gold < snowManPrice)
				{
				}

				// 쿠키
				if (Utils::CheckCollision(Buy_Selection_Icon_HitBox, CookieText_HitBox) && PlayerInfo::gold >= cookiePrice)
				{
					for (int i = 0; i < 4; ++i)
					{
						if (InventoryUi::healItem[i].GetName() == L"")
						{
							InventoryUi::healItem[i].SetInfo(L"쿠키", 10);
							PlayerInfo::slot++;
							PlayerInfo::gold -= cookiePrice;
							goldText->SetString("(" + std::to_string(PlayerInfo::gold) + "G)");
							SOUND_MGR.PlaySfx("sounds/TemMie/BuyItem.wav");
							temMieBody->SetSmiling(true);
							break;
						}
					}
				}
				else if (PlayerInfo::gold < cookiePrice)
				{
				}

				// 아이스
				if (Utils::CheckCollision(Buy_Selection_Icon_HitBox, IceText_HitBox) && PlayerInfo::gold >= icePrice)
				{
					for (int i = 0; i < 4; ++i)
					{
						if (InventoryUi::healItem[i].GetName() == L"")
						{
							InventoryUi::healItem[i].SetInfo(L"아이스", 15);
							PlayerInfo::slot++;
							PlayerInfo::gold -= icePrice;
							goldText->SetString("(" + std::to_string(PlayerInfo::gold) + "G)");
							SOUND_MGR.PlaySfx("sounds/TemMie/BuyItem.wav");
							temMieBody->SetSmiling(true);
							break;
						}
					}
				}
				else if (PlayerInfo::gold < icePrice)
				{
				}
				slotText->SetString(std::to_string(PlayerInfo::slot) + "/4");
			}
			else
			{
			}
		}
	}
#pragma endregion

#pragma region 판매 시스템
	if (isSell)
	{
		// 선택 아이콘
		if (InputMgr::GetKeyDown(sf::Keyboard::Up))
		{
			sellItem = true;
			if (!(buyTextCount <= 0))
			{
				buyTextCount--;
				buyTextPos -= 50.f;
			}
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Down))
		{
			sellItem = true;
			if (!(textCount >= 2))
			{
				buyTextCount++;
				buyTextPos += 50.f;
			}
		}
		Buy_Selection_Icon->SetPosition({ snowManText->GetPosition().x + -25.f, snowManText->GetPosition().y + 15.f + textPos });
		Buy_Selection_Icon_HitBox.setPosition(Buy_Selection_Icon->GetPosition());

		if (InputMgr::GetKeyDown(sf::Keyboard::Z) && sellItem)
		{
			if (PlayerInfo::slot > 0)
			{
				// 눈사람
				if (Utils::CheckCollision(Buy_Selection_Icon_HitBox, SnowManText_HitBox))
				{
					itemName = L"눈사람";
					for (int i = 0; i < 4; ++i)
					{
						if (itemName == InventoryUi::healItem[i].GetName())
						{
							PlayerInfo::gold += 5;
							PlayerInfo::slot--;
							InventoryUi::healItem[i].SetInfo(L"", 0);
							SOUND_MGR.PlaySfx("sounds/TemMie/BuyItem.wav");
							break;
						}
					}
				}

				// 쿠키
				if (Utils::CheckCollision(Buy_Selection_Icon_HitBox, CookieText_HitBox))
				{
					itemName = L"쿠키";
					for (int i = 0; i < 4; ++i)
					{
						if (itemName == InventoryUi::healItem[i].GetName())
						{
							PlayerInfo::gold += 10;
							PlayerInfo::slot--;
							InventoryUi::healItem[i].SetInfo(L"", 0);
							SOUND_MGR.PlaySfx("sounds/TemMie/BuyItem.wav");
							break;
						}
					}
				}

				// 아이스
				if (Utils::CheckCollision(Buy_Selection_Icon_HitBox, IceText_HitBox))
				{
					itemName = L"아이스";
					for (int i = 0; i < 4; ++i)
					{
						if (itemName == InventoryUi::healItem[i].GetName())
						{
							PlayerInfo::gold += 15;
							PlayerInfo::slot--;
							InventoryUi::healItem[i].SetInfo(L"", 0);
							SOUND_MGR.PlaySfx("sounds/TemMie/BuyItem.wav");
							break;
						}
					}
				}
				goldText->SetString("(" + std::to_string(PlayerInfo::gold) + "G)");
				slotText->SetString(std::to_string(PlayerInfo::slot) + "/4");
			}
			else
			{
			}
		}
	}
#pragma endregion

	Scene::Update(dt);
}

void TemMieShop::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

	if (Variables::isDrawHitBox)
	{
		// 메뉴
		window.draw(Selection_Icon_HitBox);
		window.draw(exitText_HitBox);
		window.draw(buyText_HitBox);
		window.draw(sellText_HitBox);
		// 구매창
		window.draw(IceText_HitBox);
		window.draw(SnowManText_HitBox);
		window.draw(CookieText_HitBox);
		window.draw(Buy_Selection_Icon_HitBox);
	}
	
}

void TemMieShop::IntroText(float dt)
{
	// 인트로 텍스트
	if (isIntroText)
	{
		textTimer += dt;

		if (currentIndex >= fullText.size())
		{
			isIntro = false;
			isIntroText = false; // 다음 메뉴에서 나가기 누를때마다 트루 시켜주기
			menu = true;
		}
		else if (textTimer >= textSpeed) // 글자 출력 간격
		{
			introText->SetActive(true);
			SOUND_MGR.PlaySfx("sounds/TemMie/temText.wav");

			textTimer = 0.f;
			currentText += fullText[currentIndex];
			currentIndex++;

			introText->SetString(currentText); // 실제 텍스트 객체에 반영
			introText->SetPosition({ temShopTextWindow->GetPosition().x + 30.f, temShopTextWindow->GetPosition().y + 25.f });
		}
	}
}