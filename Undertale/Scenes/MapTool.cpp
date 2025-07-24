#include "stdafx.h"
#include "MapTool.h"
#include "Button.h"
#include "TextGo.h"
#include "SpriteGo.h"

MapTool::MapTool() : Scene(SceneIds::MapTool)
{
}

void MapTool::Init()
{
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
	Scene::Init();
}

void MapTool::Enter()
{
	Scene::Enter();
	objectTexturePaths = {
	   "graphics/spr_f_maincharad_0.png",
	   "graphics/spr_cutetable_0.png",
	   "graphics/spr_darkelevator_l_0.png",
	   "graphics/spr_darknesstotem_0.png"
	};
	backgroundTexturePaths = {
	   "graphics/bg_firstroom.png",
	   "graphics/bg_innrooms_0.png"
	};
	FRAMEWORK.SetWindowSize(1920, 1080);
	windowSize = FRAMEWORK.GetWindowSizeF();

	worldView.setSize(windowSize);
	worldView.setCenter(windowSize.x * 0.5f, windowSize.y * 0.5f);

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
				std::cout << "��ư " << index + 1 << " ����" << std::endl;
				// ���콺 ����ٴϴ� ��������Ʈ ����
				if (activeSprite)
				{
					delete activeSprite;
					activeSprite = nullptr;
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
			
			btn->SetSize({ 300.f, 300.f });
			btn->SetColor(sf::Color::Transparent, sf::Color::Red);
			btn->SetPosition({ 1020.f + (x * 325), 170.f + (y * 125.f) });
			btn->SetOrigin({ btn->GetLocalBounds().width * 0.5f, btn->GetLocalBounds().height * 0.5f });
			btn->setCallback([&, index]() {
				std::cout << "��ư " << index + 1 << " ����" << std::endl;

				// ���� ��� ����
				if (currentBackground)
				{
					RemoveGameObject(currentBackground);
				}
				// ��ġ�� ������Ʈ�� ��� ����
				for (auto sprite : placedSprites)
				{
					RemoveGameObject(sprite);
				}
				for (auto box : hitBoxes)
				{
					delete box;
				}
				for (int i = 0; i < undoStack.size(); ++i)
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
							auto it = std::find(hitBoxes.begin(), hitBoxes.end(), action.data.rect);
							if (it != hitBoxes.end())
							{
								delete* it;
								hitBoxes.erase(it);
							}
							break;
						}
						}
						std::cout << "������Ʈ ����" << std::endl;
					}
				}
				placedSprites.clear();
				hitBoxes.clear();

				// �� ��� ����
				currentBackground = (SpriteGo*)(AddGameObject(new SpriteGo(backgroundTexturePaths[index])));
				currentBackground->Reset();
				currentBackground->SetTextureId(backgroundTexturePaths[index]);
				currentBackground->SetScale({ 1.f, 1.f });
				currentBackground->SetOrigin({currentBackground->GetLocalBounds().width * 0.5f,currentBackground->GetLocalBounds().height});
				currentBackground->SetPosition({ 200.f, 200.f });
				currentBackground->sortingLayer = SortingLayers::Background;
				currentBackground->sortingOrder = 0;
				
			});
		}
	}

	for (int i = 0; i < objectTexturePaths.size(); ++i)
	{
		objectSprites[i]->SetTextureId(objectTexturePaths[i]);
		objectSprites[i]->SetPosition({ objectButtons[i]->GetPosition().x,objectButtons[i]->GetPosition().y });
	}

	for (int i = 0; i < backgroundTexturePaths.size(); ++i)
	{
		backgroundSprites[i]->SetTextureId(backgroundTexturePaths[i]);
		backgroundSprites[i]->sortingOrder = 0;
		backgroundSprites[i]->SetScale({ 0.5f,0.4f });
		backgroundSprites[i]->SetOrigin({ backgroundSprites[i]->GetLocalBounds().width * 0.5f, backgroundSprites[i]->GetLocalBounds().height });
		backgroundSprites[i]->SetPosition({ backgroundButtons[i]->GetPosition().x,backgroundButtons[i]->GetPosition().y });
	}

	hitBox->SetSize({ 100.f, 100.f });
	hitBox->SetPosition({ 0.f,0.f });
	hitBox->setCallback([&]() {
		dragMode = true;
		std::cout << "�巡�� ��� ON" << std::endl;
		});
}

void MapTool::Exit()
{
	objectButtons.clear();

	if (activeSprite)
	{
		delete activeSprite;
		activeSprite = nullptr;
	}
}

void MapTool::Update(float dt)
{
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

	// �� �̵� �ӵ�
	float moveSpeed = 100.f;

	// �� �̵�
	if (InputMgr::GetKey(sf::Keyboard::Left))
	{
		worldView.move(-moveSpeed * dt, 0.f);
		FRAMEWORK.GetWindow().setView(worldView);
	}
	if (InputMgr::GetKey(sf::Keyboard::Right))
	{
		worldView.move(moveSpeed * dt, 0.f);
		FRAMEWORK.GetWindow().setView(worldView);
	}
	if (InputMgr::GetKey(sf::Keyboard::Up))
	{
		worldView.move(0.f, -moveSpeed * dt);
		FRAMEWORK.GetWindow().setView(worldView);
	}
	if (InputMgr::GetKey(sf::Keyboard::Down))
	{
		worldView.move(0.f, moveSpeed * dt);
		FRAMEWORK.GetWindow().setView(worldView);
	}
	
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
			hitBoxes.push_back(newRect);

			UndoAction action;
			action.type = UndoAction::Type::HitBox;
			action.data.rect = newRect;
			undoStack.push_back(action);

			dragHitBox.setSize({ 0.f, 0.f });
		}
	}

	// ���콺 ����ٴϴ� ��������Ʈ ��ġ ����
	if (activeSprite)
	{
		sf::Vector2i mousePixel = sf::Mouse::getPosition(FRAMEWORK.GetWindow());
		sf::Vector2f mouseWorld = FRAMEWORK.GetWindow().mapPixelToCoords(mousePixel);
		activeSprite->SetPosition(mouseWorld);

		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
		{
			auto placed = (SpriteGo*)(AddGameObject(new SpriteGo(activeSprite->GetTextureId())));
			placed->Reset();
			placed->sortingOrder = 1;
			placed->SetPosition(mouseWorld);
			placed->SetOrigin(Origins::MC);
			
			placedSprites.push_back(placed);
			UndoAction action;
			action.type = UndoAction::Type::Sprite;
			action.data.sprite = placed;
			undoStack.push_back(action);
			std::cout << "�ʿ� ������Ʈ ��ġ �Ϸ�" << std::endl;

			delete activeSprite;
			activeSprite = nullptr;
		}

		// ESC ������ ���
		if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
		{
			delete activeSprite;
			activeSprite = nullptr;
			std::cout << "��ġ ���" << std::endl;
		}
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Return))
	{
		SCENE_MGR.ChangeScene(SceneIds::test);
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
				auto it = std::find(hitBoxes.begin(), hitBoxes.end(), action.data.rect);
				if (it != hitBoxes.end())
				{
					delete* it;
					hitBoxes.erase(it);
				}
				break;
			}
			}
			std::cout << "������Ʈ ����" << std::endl;
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
	for (auto& box : hitBoxes)
	{
		window.draw(*box);
	}
}
