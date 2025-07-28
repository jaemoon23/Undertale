#include "stdafx.h"
#include <fstream>
#include "MapTool.h"
#include "Button.h"
#include "TextGo.h"
#include "SpriteGo.h"
#include "json.hpp"

MapTool::MapTool() : Scene(SceneIds::MapTool), grid(sf::Lines), gridOffset(0.f, 0.f)
{
}

void MapTool::Init()
{
	fontIds.push_back("fonts/DungGeunMo.ttf");
	for (int i = 0; i < objectTexturePaths.size(); ++i)
	{
		texIds.push_back(objectTexturePaths[i]);
		objectSprites.push_back((SpriteGo*)(AddGameObject)(new SpriteGo(objectTexturePaths[i])));
	}

	for (int i = 0; i < backgroundTexturePaths.size(); ++i)
	{
		texIds.push_back(backgroundTexturePaths[i]);
		backgroundSprites.push_back((SpriteGo*)(AddGameObject)(new SpriteGo(backgroundTexturePaths[i])));
	}

	objectButtons.push_back((Button*)(AddGameObject(new Button("button1"))));
	objectButtons.push_back((Button*)(AddGameObject(new Button("button2"))));
	objectButtons.push_back((Button*)(AddGameObject(new Button("button3"))));
	objectButtons.push_back((Button*)(AddGameObject(new Button("button4"))));

	backgroundButtons.push_back((Button*)(AddGameObject(new Button("backButton1"))));
	backgroundButtons.push_back((Button*)(AddGameObject(new Button("backButton2"))));

	hitBox = (Button*)AddGameObject(new Button("HitBox"));

	hitBoxText = (TextGo*)AddGameObject(new TextGo("fonts/DungGeunMo.ttf"));
	saveBoxText = (TextGo*)AddGameObject(new TextGo("fonts/DungGeunMo.ttf"));
	backText = (TextGo*)AddGameObject(new TextGo("fonts/DungGeunMo.ttf"));
	objectText = (TextGo*)AddGameObject(new TextGo("fonts/DungGeunMo.ttf"));
	Scene::Init();
}

void MapTool::Enter()
{
	Scene::Enter();
	FRAMEWORK.SetWindowSize(1920, 1080);
	windowSize = FRAMEWORK.GetWindowSizeF();

	worldView.setSize(windowSize);
	worldView.setCenter(windowSize.x * 0.5f, windowSize.y * 0.5f);
	// 그리드
	gridDraw = false;
	for (int y = 0; y <= gridHeight; y += cellSize)
	{
		grid.append(sf::Vertex(sf::Vector2f(gridOffset.x, gridOffset.y + y), sf::Color::Red));
		grid.append(sf::Vertex(sf::Vector2f(gridOffset.x + gridWidth, gridOffset.y + y), sf::Color::Red));
	}
	for (int x = 0; x <= gridWidth; x += cellSize)
	{
		grid.append(sf::Vertex(sf::Vector2f(gridOffset.x + x, gridOffset.y), sf::Color::Red));
		grid.append(sf::Vertex(sf::Vector2f(gridOffset.x + x, gridOffset.y + gridHeight), sf::Color::Red));
	}
	objectTexturePaths = {
	   "graphics/spr_f_maincharad_0.png",
	   "graphics/spr_cutetable_0.png",
	   "graphics/spr_darkelevator_l_0.png",
	   "graphics/spr_darknesstotem_0.png"
	};
	backgroundTexturePaths = {
	   "graphics/bg_firstroom.png",
	   "graphics/back2.png"
	};

	const int maxColumns = 5;
	for (int y = 0; y < 5; ++y)
	{
		for (int x = 0; x < maxColumns; ++x)
		{
			int index = (y * maxColumns) + x;
			if (index >= objectButtons.size())
			{
				break;
			}
			auto btn = objectButtons[index];

			btn->SetSize({ 100.f, 100.f });
			btn->SetColor(sf::Color::Transparent, sf::Color::Green);
			btn->SetPosition({ 1020.f + (x * 125), 700.f + (y * 125.f) });
			btn->SetOrigin({ btn->GetLocalBounds().width * 0.5f, btn->GetLocalBounds().height * 0.5f });

			btn->setCallback([&, index]() {
				std::cout << "버튼 " << index + 1 << " 누름" << std::endl;
				// 마우스 따라다니는 스프라이트 생성
				if (activeSprite)
				{
					RemoveGameObject(activeSprite);
				}
				activeSprite = new SpriteGo(objectTexturePaths[index]);
				activeSprite->SetTextureId(objectTexturePaths[index]);
				activeSprite->SetOrigin(Origins::MC);
				activeSprite->Reset();
				activeSprite->sortingOrder = 1;
				});
		}
	}
	for (int y = 0; y < 5; ++y)
	{
		for (int x = 0; x < maxColumns; ++x)
		{
			int index = (y * maxColumns) + x;
			if (index >= backgroundButtons.size())
			{
				break;
			}
			auto btn = backgroundButtons[index];

			btn->SetSize({ 300.f, 200.f });
			btn->SetColor(sf::Color::Transparent, sf::Color::Red);
			btn->SetPosition({ 1020.f + (x * 325), 170.f + (y * 125.f) });
			btn->SetOrigin({ btn->GetLocalBounds().width * 0.5f, btn->GetLocalBounds().height * 0.5f });
			btn->setCallback([&, index]() {
				std::cout << "버튼 " << index + 1 << " 누름" << std::endl;

				// 기존 배경 삭제
				if (currentBackground)
				{
					RemoveGameObject(currentBackground);
				}
				// 배치된 오브젝트들 모두 제거
				for (auto sprite : placedSprites)
				{
					RemoveGameObject(sprite);
				}
				for (auto& info : hitBoxes)
				{
					delete info.shape;
				}
				hitBoxes.clear();
				placedSprites.clear();

				// 새 배경 생성
				currentBackground = (SpriteGo*)(AddGameObject(new SpriteGo(backgroundTexturePaths[index])));
				currentBackground->Reset();

				currentBackground->SetTextureId(backgroundTexturePaths[index]);
				currentBackground->SetScale({ 1.f, 1.f });

				sf::FloatRect bounds = currentBackground->GetLocalBounds();
				currentBackground->SetOrigin({ bounds.width * 0.5f, bounds.height * 0.5f });

				currentBackground->SetPosition({ 320.f , 240.f });
				currentBackground->sortingLayer = SortingLayers::Background;
				currentBackground->sortingOrder = 0;

				std::cout << "포지션: " << currentBackground->GetPosition().x << ", " << currentBackground->GetPosition().y << std::endl;
				std::cout << "바운드: " << bounds.width << ", " << bounds.height << std::endl;
				});
		}
	}

	for (int i = 0; i < objectTexturePaths.size(); ++i)
	{
		objectSprites[i]->SetTextureId(objectTexturePaths[i]);
		objectSprites[i]->SetOrigin(Origins::MC);
		objectSprites[i]->SetPosition({ objectButtons[i]->GetPosition().x + 50.f,objectButtons[i]->GetPosition().y + 40.f });
	}


	for (int i = 0; i < backgroundTexturePaths.size(); ++i)
	{
		backgroundSprites[i]->SetTextureId(backgroundTexturePaths[i]);
		backgroundSprites[i]->sortingOrder = 0;
		backgroundSprites[i]->SetScale({ 0.5f,0.4f });
		backgroundSprites[i]->SetOrigin({ backgroundSprites[i]->GetLocalBounds().width * 0.5f, backgroundSprites[i]->GetLocalBounds().height });
		backgroundSprites[i]->SetPosition({ backgroundButtons[i]->GetPosition().x + 150.f, backgroundButtons[i]->GetPosition().y + 150.f });
	}

	hitBox->SetSize({ 150.f, 50.f });
	hitBox->SetColor(sf::Color::Transparent, sf::Color::Blue);
	hitBox->SetPosition({ 20.f,500.f });
	hitBox->setCallback([&]() {
		dragMode = true;
		std::cout << "드래그 모드 ON" << std::endl;
		});
	hitBoxText->SetString("HitBox");
	hitBoxText->SetCharacterSize(50.f);
	hitBoxText->SetFillColor(sf::Color::Blue);
	hitBoxText->SetPosition({ hitBox->GetPosition().x, hitBox->GetPosition().y - 10.f});
	

	saveButton = (Button*)AddGameObject(new Button("SaveButton"));
	saveButton->SetSize({ 150.f, 50.f });
	saveButton->SetColor(sf::Color::Transparent, sf::Color::Blue);
	saveButton->SetPosition({ 200.f,500.f });
	saveButton->setCallback([&]() {
		jsonInput(); 
		std::cout << "저장 완료!" << std::endl;
		});
	saveBoxText->SetString("save");
	saveBoxText->SetCharacterSize(50.f);
	saveBoxText->SetFillColor(sf::Color::Blue);
	saveBoxText->SetPosition({ saveButton->GetPosition().x + 25.f, saveButton->GetPosition().y - 10.f });

	backText->SetString("BackGround");
	backText->SetCharacterSize(50.f);
	backText->SetFillColor(sf::Color::White);
	backText->SetPosition({ 1200.f, 100.f});

	objectText->SetString("Object");
	objectText->SetCharacterSize(50.f);
	objectText->SetFillColor(sf::Color::White);
	objectText->SetPosition({ 1200.f, 600.f});

	

}

void MapTool::Exit()
{
	/*objectButtons.clear();*/

	if (activeSprite)
	{
		delete activeSprite;
		activeSprite = nullptr;
	}
}

void MapTool::Update(float dt)
{
	// 마우스 포지션
	sf::Vector2i pixelPos = sf::Mouse::getPosition(FRAMEWORK.GetWindow());
	sf::Vector2f worldPos = FRAMEWORK.GetWindow().mapPixelToCoords(pixelPos);

	if (InputMgr::GetKeyDown(sf::Keyboard::T))
	{
		SCENE_MGR.ChangeScene(SceneIds::Title);
	}
	// 그리드
	if (InputMgr::GetKeyDown(sf::Keyboard::F2))
	{
		gridDraw = !gridDraw;
	}

	if (gridDraw)
	{
		cellX = (worldPos.x - gridOffset.x) / cellSize;
		cellY = (worldPos.y - gridOffset.y) / cellSize;

		if (cellX >= 0 && cellX < gridWidth / cellSize && cellY >= 0 && cellY < gridHeight / cellSize)
		{
			if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
			{
				std::cout << "(" << cellX << ", " << cellY << ")" << std::endl;
			}
		}
	}
	
	// zoom in, out 
	static float currentZoom = 1.f;
	const float zoomStep = 0.1f;
	const float minZoom = 0.2f;
	const float maxZoom = 1.0f;

	float delta = InputMgr::GetMouseWheelDelta();
	if (delta != 0.f)
	{
		float newZoom = currentZoom + (delta < 0.f ? zoomStep : -zoomStep);
		newZoom = Utils::Clamp(newZoom, minZoom, maxZoom);

		if (newZoom != currentZoom)
		{
			float zoomFactor = newZoom / currentZoom;
			currentZoom = newZoom;

			worldView.zoom(zoomFactor);
			FRAMEWORK.GetWindow().setView(worldView);
		}
	}

	// 뷰 이동 속도
	float moveSpeed = 300.f;

	// 뷰 이동
	if (InputMgr::GetKey(sf::Keyboard::A))
	{
		worldView.move(-moveSpeed * dt, 0.f);
		FRAMEWORK.GetWindow().setView(worldView);
	}
	if (InputMgr::GetKey(sf::Keyboard::D))
	{
		worldView.move(moveSpeed * dt, 0.f);
		FRAMEWORK.GetWindow().setView(worldView);
	}
	if (InputMgr::GetKey(sf::Keyboard::W))
	{
		worldView.move(0.f, -moveSpeed * dt);
		FRAMEWORK.GetWindow().setView(worldView);
	}
	if (InputMgr::GetKey(sf::Keyboard::S))
	{
		worldView.move(0.f, moveSpeed * dt);
		FRAMEWORK.GetWindow().setView(worldView);
	}
	
	// 히트박스 드래그
	if (dragMode)
	{
		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
		{
			isDragging = true;
			dragStartPos = FRAMEWORK.GetWindow().mapPixelToCoords(sf::Mouse::getPosition(FRAMEWORK.GetWindow()));
			dragHitBox.setPosition(dragStartPos);
			dragHitBox.setSize({ 0.f, 0.f });
			dragHitBox.setFillColor(sf::Color::Transparent);
			dragHitBox.setOutlineColor(sf::Color::Green);
			dragHitBox.setOutlineThickness(1.f);
		}
		else if (InputMgr::GetMouseButton(sf::Mouse::Left) && isDragging)
		{
			sf::Vector2f currentPos = FRAMEWORK.GetWindow().mapPixelToCoords(sf::Mouse::getPosition(FRAMEWORK.GetWindow()));
			sf::Vector2f size = currentPos - dragStartPos;

			dragHitBox.setSize({ std::abs(size.x), std::abs(size.y) });
			dragHitBox.setPosition({ std::min(dragStartPos.x, currentPos.x), std::min(dragStartPos.y, currentPos.y) });
		}
		else if (InputMgr::GetMouseButtonUp(sf::Mouse::Left) && isDragging)
		{
			isDragging = false;
			dragMode = false;

			auto newRect = new sf::RectangleShape(dragHitBox);

			// 히트박스 타입 결정
			HitBoxType boxType = HitBoxType::Wall; // 기본: 벽
			std::string fieldName = "";
			if (InputMgr::GetKey(sf::Keyboard::Num1)) // Num1 누르면 씬 전환
			{
				boxType = HitBoxType::SceneChanege;
				newRect->setOutlineColor(sf::Color(128, 0, 128)); // 보라색
			}
			else if (InputMgr::GetKey(sf::Keyboard::Q))
			{
				boxType = HitBoxType::NextScene;
				fieldName = "NextScene";   
				newRect->setOutlineColor(sf::Color(255, 165, 0));
			}
			else if (InputMgr::GetKey(sf::Keyboard::E))
			{
				boxType = HitBoxType::PrevScene;
				fieldName = "PrevScene";   
				newRect->setOutlineColor(sf::Color(135, 206, 250));
			}
			else if (InputMgr::GetKey(sf::Keyboard::Num2))
			{
				boxType = HitBoxType::Battle;
				fieldName = "BattleZone";   
				newRect->setOutlineColor(sf::Color::Red); 
			}
			else if (InputMgr::GetKey(sf::Keyboard::Num3))
			{
				boxType = HitBoxType::Event;
				fieldName = "Event";
				newRect->setOutlineColor(sf::Color::Blue);
			}
			else if (InputMgr::GetKey(sf::Keyboard::Num4))
			{
				boxType = HitBoxType::Door;
				fieldName = "Door";
				newRect->setOutlineColor(sf::Color::Yellow);
			}
			else if (InputMgr::GetKey(sf::Keyboard::Num5))
			{
				boxType = HitBoxType::Switch;
				fieldName = "Switch";
				newRect->setOutlineColor(sf::Color(170, 255, 195));
			}
			else if (InputMgr::GetKey(sf::Keyboard::Num6))
			{
				boxType = HitBoxType::Signs;
				fieldName = "Signs";
				newRect->setOutlineColor(sf::Color::White);
			}
			else
			{
				boxType = HitBoxType::Wall;
				newRect->setOutlineColor(sf::Color::Green);
			}

			newRect->setFillColor(sf::Color::Transparent);
			newRect->setOutlineThickness(1.f);

			// 히트박스 저장
			hitBoxes.push_back({ newRect, boxType });

			// Undo에 저장
			UndoAction action;
			action.type = UndoAction::Type::HitBox;
			action.data.rect = newRect; 
			undoStack.push_back(action);

			dragHitBox.setSize({ 0.f, 0.f });

			std::string typeStr;
			switch (boxType)
			{
			case HitBoxType::Wall:
				typeStr = "Wall";
				break;
			case HitBoxType::SceneChanege:
				typeStr = "SceneChanege";
				break;
			case HitBoxType::NextScene:
				typeStr = "NextScene";
				break;
			case HitBoxType::PrevScene:
				typeStr = "PrevScene";
				break;
			case HitBoxType::Battle: 
				typeStr = "Battle";
				break;
			case HitBoxType::Switch:
				typeStr = "Switch";
				break;
			case HitBoxType::Door:
				typeStr = "Door";
				break;
			case HitBoxType::Event:
				typeStr = "Event";
				break;
			case HitBoxType::Signs:
				typeStr = "Signs";
				break;
			}

			std::cout << "히트박스 생성됨 (타입: " << typeStr << ")" << std::endl;
		}
		
	}

	// 마우스 따라다니는 스프라이트
	if (activeSprite)
	{
		activeSprite->SetPosition(worldPos);

		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
		{
			auto placed = (SpriteGo*)(AddGameObject(new SpriteGo(activeSprite->GetTextureId())));
			placed->Reset();
			placed->sortingOrder = 1;
			placed->SetPosition(worldPos);
			placed->SetOrigin(Origins::MC);
			
			placedSprites.push_back(placed);
			UndoAction action;
			action.type = UndoAction::Type::Sprite;
			action.data.sprite = placed;
			undoStack.push_back(action);
			std::cout << "맵에 오브젝트 배치 완료" << std::endl;

			delete activeSprite;
			activeSprite = nullptr;
		}

		// ESC 누르면 취소
		if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
		{
			delete activeSprite;
			activeSprite = nullptr;
			std::cout << "배치 취소" << std::endl;
		}
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Z))
	{
		if (!undoStack.empty())
		{
			UndoAction action = undoStack.back();
			undoStack.pop_back();

			switch (action.type)
			{
			case UndoAction::Type::Sprite:
			{
				SpriteGo* spriteToDelete = action.data.sprite;
				auto it = std::find(placedSprites.begin(), placedSprites.end(), spriteToDelete);
				if (it != placedSprites.end())
				{
					RemoveGameObject(*it);      
					placedSprites.erase(it);   
				}
				break;
			}
			case UndoAction::Type::HitBox:
			{
				auto it = std::find_if(hitBoxes.begin(), hitBoxes.end(), [&](const HitBoxInfo& info) { return info.shape == action.data.rect; });
				if (it != hitBoxes.end())
				{
					delete it->shape;
					hitBoxes.erase(it);
				}
				break;
			}
			}
			std::cout << "오브젝트 삭제" << std::endl;
		}
	}
	Scene::Update(dt);
}

void MapTool::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	if (activeSprite)
	{
		activeSprite->Draw(window);
	}
	if (dragMode || isDragging)
	{
		window.draw(dragHitBox);
	}
	for (auto& info : hitBoxes)
	{
		window.draw(*info.shape);
	}
	if (gridDraw)
	{
		window.draw(grid);
	}
}

void MapTool::jsonInput()
{
	nlohmann::json total;

	nlohmann::json map;
	map["background"] = {
	{"textureId", currentBackground->GetTextureId()},
	{"position", {
		currentBackground->GetPosition().x,
		currentBackground->GetPosition().y
	}},
	{"scale", {
		currentBackground->GetScale().x,
		currentBackground->GetScale().y
	}}
	};

	// 오브젝트 리스트
	for (auto& sprite : placedSprites)
	{
		map["objects"].push_back({
			{"textureId", sprite->GetTextureId()},
			{"position", {sprite->GetPosition().x, sprite->GetPosition().y}},
			{ "scale", {currentBackground->GetScale().x, currentBackground->GetScale().y} }
		});
	}

	// 히트박스 리스트
	for (auto& hit : hitBoxes)
	{
		sf::Vector2f pos = hit.shape->getPosition();
		sf::Vector2f size = hit.shape->getSize();
		std::string typeStr;
		switch (hit.type)
		{
		case HitBoxType::Wall:
			typeStr = "Wall";
			break;
		case HitBoxType::SceneChanege:
			typeStr = "SceneChanege";
			break;
		case HitBoxType::NextScene:
			typeStr = "NextScene";
			break;
		case HitBoxType::PrevScene:
			typeStr = "PrevScene";
			break;
		case HitBoxType::Battle:
			typeStr = "Battle";
			break;
		case HitBoxType::Switch:
			typeStr = "Switch";
			break;
		case HitBoxType::Door:
			typeStr = "Door";
			break;
		case HitBoxType::Event:
			typeStr = "Event";
			break;
		case HitBoxType::Signs:
			typeStr = "Signs";
			break;
		}

		map["hitboxes"].push_back({
			{"position", {pos.x, pos.y}},
			{"size", {size.x, size.y}},
			{"type", typeStr}
			});
	}

	auto fileExists = [](const std::string& filename) {
		std::ifstream file(filename);
		return file.good();
	};

	int mapIndex = 0;
	std::string mapName;

	while (fileExists("map" + std::to_string(mapIndex) + ".json"))
	{
		mapIndex++;
	}

	mapName = "map" + std::to_string(mapIndex);

	total[mapName] = map;

	std::ofstream outFile(mapName + ".json");
	outFile << total.dump(4);
	std::cout << "맵 저장 완료: " << mapName << ".json" << std::endl;

}