#include "stdafx.h"
#include "MapTool.h"
#include "Button.h"
#include "InputText.h"
#include "TextGo.h"
#include "SpriteGo.h"

MapTool::MapTool() : Scene(SceneIds::MapTool), grid(sf::Lines), gridOffset(200.f, 200.f)
{
	
}

void MapTool::Init()
{
	fontIds.push_back("fonts/DungGeunMo.ttf");
	texIds.push_back("graphics/bg_firstroom.png");
	texIds.push_back("graphics/spr_f_maincharad_0.png");

	
	back = (SpriteGo*)AddGameObject(new SpriteGo("graphics/bg_firstroom.png"));
	ch = (SpriteGo*)AddGameObject(new SpriteGo("graphics/spr_f_maincharad_0.png"));
	object = (TextGo*)AddGameObject(new TextGo("fonts/DungGeunMo.ttf"));

	buttons.push_back((Button*)(AddGameObject(new Button("button1"))));
	buttons.push_back((Button*)(AddGameObject(new Button("button2"))));
	buttons.push_back((Button*)(AddGameObject(new Button("button3"))));
	buttons.push_back((Button*)(AddGameObject(new Button("button4"))));

	sprites.push_back((SpriteGo*)(AddGameObject(new SpriteGo("sp1"))));
	
	
	Scene::Init();
}

void MapTool::Enter()
{
	Scene::Enter();
	gridDraw = false;
	FRAMEWORK.SetWindowSize(1920, 1080);
	windowSize = FRAMEWORK.GetWindowSizeF();

	//back->SetOrigin({ 680.f * 0.5f, 260.f * 0.5f });
	back->SetPosition({ 200.f,200 });

	worldView.setSize(windowSize);
	worldView.setCenter(windowSize.x * 0.5f, windowSize.y * 0.5f);

	objectSheets.setSize({ 510.f, 700.f });
	objectSheets.setFillColor(sf::Color::Transparent);
	objectSheets.setOutlineColor(sf::Color::White);
	objectSheets.setOutlineThickness(2.f);
	objectSheets.setPosition({ 1000.f, 150.f });


	object->SetString("Object");
	object->SetCharacterSize(100);
	object->SetFillColor(sf::Color::White);
	object->SetPosition({ 1100.f, 20.f });

	for (int i = 0; i < buttons.size(); ++i)
	{
		auto btn = buttons[i];

		btn->SetSize({ 100.f, 100.f });
		btn->SetColor(sf::Color::Transparent, sf::Color::Red);
		btn->SetPosition({ 1020.f + (i * 125), 170.f });
		btn->SetSize({ 100.f, 100.f });
		btn->SetOrigin({ btn->GetLocalBounds().width * 0.5f, btn->GetLocalBounds().height * 0.5f });
		btn->setCallback([&, i]() {
			std::cout << "버튼 " << i + 1 << " 누름" << std::endl;
			});
		
	}
	ch->SetPosition({ buttons[0]->GetPosition().x,buttons[0]->GetPosition().y});
	
	// 가로줄
	for (int y = 0; y <= gridHeight; y += cellSize)
	{
		grid.append(sf::Vertex(sf::Vector2f(gridOffset.x, gridOffset.y + y), sf::Color::Green));       // 왼쪽
		grid.append(sf::Vertex(sf::Vector2f(gridOffset.x + gridWidth, gridOffset.y + y), sf::Color::Green)); // 오른쪽
	}

	// 세로줄
	for (int x = 0; x <= gridWidth; x += cellSize)
	{
		grid.append(sf::Vertex(sf::Vector2f(gridOffset.x + x, gridOffset.y), sf::Color::Green));       // 위쪽
		grid.append(sf::Vertex(sf::Vector2f(gridOffset.x + x, gridOffset.y + gridHeight), sf::Color::Green)); // 아래쪽
	}
}

void MapTool::Exit()
{
	buttons.clear();
}

void MapTool::Update(float dt)
{
	const float zoomFactor = 1.1f; // 줌 배율
	if (InputMgr::GetKeyDown(sf::Keyboard::F2))
	{
		gridDraw = !gridDraw;
	}
	
	
	sf::Vector2i pixelPos = sf::Mouse::getPosition(FRAMEWORK.GetWindow());
	sf::Vector2f worldPos = FRAMEWORK.GetWindow().mapPixelToCoords(pixelPos);

	if (InputMgr::GetKeyDown(sf::Keyboard::Up))
	{
		worldView.setCenter(worldPos);
		worldView.zoom(1.0f / zoomFactor);
	}
	else if (InputMgr::GetKeyDown(sf::Keyboard::Down))
	{
		worldView.setCenter(worldPos);
		worldView.zoom(zoomFactor);
		if (worldView.getSize().x >= 1920.f || worldView.getSize().y < 1080.f)
		{
			worldView.setSize(windowSize);
			worldView.setCenter(windowSize.x * 0.5f, windowSize.y * 0.5f);
		}
	}

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		std::cout << worldPos.x << ", " << worldPos.y << std::endl;
	}
	if (gridDraw)
	{
		cellX = (worldPos.x - gridOffset.x) / cellSize;
		cellY = (worldPos.y - gridOffset.y) / cellSize;

		if (cellX >= 0 && cellX < gridWidth / cellSize && cellY >= 0 && cellY < gridHeight / cellSize)
		{
			if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
			{
				std::cout << "선택한 셀: (" << cellX + 1 << ", " << cellY + 1 << ")" << std::endl;
			}
		}
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Return))
	{
		SCENE_MGR.ChangeScene(SceneIds::test);
	}
	Scene::Update(dt);
}

void MapTool::Draw(sf::RenderWindow& window)
{
	if (gridDraw)
	{
		window.draw(grid);
	}
	window.draw(objectSheets);
	
	Scene::Draw(window);
}
