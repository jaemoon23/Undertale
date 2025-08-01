#include "stdafx.h"
#include "Scene.h"
#include <fstream>
#include "json.hpp"
#include "Player.h"
#include "SpriteGo.h"

Scene::Scene(SceneIds id)
	: Id(id)
{
}

void Scene::Init()
{
	for (auto obj : gameObjects)
	{
		obj->Init();
	}

	for (auto obj : objectsToAdd)
	{
		obj->Init();
	}
}

void Scene::Release()
{
	ApplyPendingChanges();
	
	for (auto obj : gameObjects)
	{
		obj->Release();
		delete obj;
	}
	gameObjects.clear();
}

void Scene::Enter()
{
	TEXTURE_MGR.Load(texIds);
	FONT_MGR.Load(fontIds);
	SOUNDBUFFER_MGR.Load(soundIds);

	for (auto obj : gameObjects)
	{
		obj->Reset();
	}

	for (auto obj : objectsToAdd)
	{
		obj->Reset();
	}
}

void Scene::Exit()
{
	ApplyPendingChanges();

	TEXTURE_MGR.Unload(texIds);
	FONT_MGR.Unload(fontIds);
	SOUNDBUFFER_MGR.Unload(soundIds);
}

void Scene::Update(float dt)
{
	for (auto obj : gameObjects)
	{
		if (obj->GetActive())
		{
			obj->Update(dt);
		}
	}
}

void Scene::Draw(sf::RenderWindow& window)
{
	std::list<GameObject*> sortedObjects(gameObjects);
	sortedObjects.sort(DrawOrderComparer());

	window.setView(worldView);
	bool isUiView = false;

	for (auto obj : sortedObjects)
	{
		if (obj->sortingLayer >= SortingLayers::UI && !isUiView)
		{
			window.setView(uiView);
			isUiView = true;
		}

		if (obj->GetActive())
		{
			obj->Draw(window);
		}
	}
	ApplyPendingChanges();
}

void Scene::ApplyPendingChanges()
{
	for (GameObject* go : objectsToAdd)
	{
		if (std::find(gameObjects.begin(), gameObjects.end(), go) == gameObjects.end())
		{
			gameObjects.push_back(go);
		}
	}
	objectsToAdd.clear();

	for (GameObject* go : objectsToRemove)
	{
		gameObjects.remove(go);
		if (go != nullptr)
		{
			go->Release();
			delete go;
		}
	}
	objectsToRemove.clear();

}

GameObject* Scene::AddGameObject(GameObject* go)
{
	objectsToAdd.push_back(go);
	return go;
}

void Scene::RemoveGameObject(GameObject* go)
{
	go->SetActive(false);
	objectsToRemove.push_back(go);
}

GameObject* Scene::FindGameObject(const std::string& name)
{
	for (auto obj : gameObjects)
	{
		if (obj->GetName() == name)
		{
			return obj;
		}
	}
	
	for (auto obj : objectsToAdd)
	{
		if (obj->GetName() == name)
		{
			return obj;
		}
	}
	
	return nullptr;
}

std::vector<GameObject*> Scene::FindGameObjects(const std::string& name)
{
	std::vector<GameObject*> results;
	
	for (auto obj : gameObjects)
	{
		if (obj->GetName() == name)
		{
			results.push_back(obj);
		}
	}
	
	for (auto obj : objectsToAdd)
	{
		if (obj->GetName() == name)
		{
			results.push_back(obj);
		}
	}
	
	return results;
}

void Scene::FindGameObjects(const std::string& name, std::vector<GameObject*>& results)
{
	for (auto obj : gameObjects)
	{
		if (obj->GetName() == name)
		{
			results.push_back(obj);
		}
	}
	
	for (auto obj : objectsToAdd)
	{
		if (obj->GetName() == name)
		{
			results.push_back(obj);
		}
	}
}

sf::Vector2f Scene::ScreenToWorld(sf::Vector2i screenPos)
{
	return FRAMEWORK.GetWindow().mapPixelToCoords(screenPos, worldView);
}

sf::Vector2i Scene::WorldToScreen(sf::Vector2f worldPos)
{
	return FRAMEWORK.GetWindow().mapCoordsToPixel(worldPos, worldView);
}

sf::Vector2f Scene::ScreenToUi(sf::Vector2i screenPos)
{
	return FRAMEWORK.GetWindow().mapPixelToCoords(screenPos, uiView);
}

sf::Vector2i Scene::UiToScreen(sf::Vector2f uiPos)
{
	return FRAMEWORK.GetWindow().mapCoordsToPixel(uiPos, uiView);
}
void Scene::LoadMapFromJson(const std::string& filename, const std::string& mapName, Player* player, SpriteGo* background, std::vector<SpriteGo*>& objects, std::vector<HitBoxInfo1>& hitboxes)
{
	std::ifstream in(filename);
	if (!in)
	{
		std::cerr << filename << " 파일을 열 수 없습니다!" << std::endl;
		return;
	}

	nlohmann::json j;
	in >> j;

	if (!j.contains(mapName))
	{
		std::cerr << "맵 키 '" << mapName << "' 가 JSON 파일에 존재하지 않습니다!" << std::endl;
		return;
	}

	auto& mapData = j[mapName]; // 이제 외부에서 키를 전달받음

	// 배경
	std::string bgTex = mapData["background"]["textureId"];
	sf::Vector2f bgPos(mapData["background"]["position"][0], mapData["background"]["position"][1]);
	sf::Vector2f bgScale(mapData["background"]["scale"][0], mapData["background"]["scale"][1]);

	background->SetTextureId(bgTex);
	background->SetOrigin(Origins::MC);
	background->SetPosition(bgPos);
	background->SetScale(bgScale);

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
			player->sortingLayer = SortingLayers::Foreground;
			player->sortingOrder = 4;
			playerPlaced = true;
		}
		else
		{
			auto sprite = (SpriteGo*)AddGameObject(new SpriteGo(texId));
			sprite->SetTextureId(texId);
			sprite->SetOrigin(Origins::MC);
			sprite->SetPosition(pos);
			sprite->SetScale(scale);
			sprite->sortingLayer = SortingLayers::Foreground;
			sprite->sortingOrder = 0;
			objects.push_back(sprite);
		}
	}

	// 히트박스
	for (auto& box : mapData["hitboxes"])
	{
		sf::Vector2f pos(box["position"][0], box["position"][1]);
		sf::Vector2f size(box["size"][0], box["size"][1]);
		std::string typeStr = box["type"];

		auto rect = new sf::RectangleShape(size);
		rec.push_back(rect);
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
		else if (typeStr == "Event")
		{
			rect->setOutlineColor(sf::Color::Blue);
		}
		else if (typeStr == "Door")
		{
			rect->setOutlineColor(sf::Color::Yellow);
		}
		else if (typeStr == "swicth")
		{
			rect->setOutlineColor(sf::Color(170, 255, 195)); // ��Ʈ��
		}
		else if (typeStr == "Signs")
		{
			rect->setOutlineColor(sf::Color::White);
		}


		rect->setOutlineThickness(1.f);
		hitboxes.push_back({ rect, typeStr });
	}
}
