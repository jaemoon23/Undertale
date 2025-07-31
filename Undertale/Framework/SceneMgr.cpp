#include "stdafx.h"
#include "SceneMgr.h"
#include "SceneDev1.h"
#include "SceneIntro.h"
#include "MapTool.h"
#include "Map0.h"
//#include "SceneDev2.h"
#include "SceneBattle.h"
//#include "SceneTest.h"
#include "SceneTitle.h"
#include "Map1.h"
#include "Map2.h"
#include "Map3.h"
#include "Map4.h"
#include "Map5.h"
#include "MapPapyrus.h"
#include "MapSans.h"
#include "TemMieShop.h"
#include "SceneEnding.h"

void SceneMgr::Init()
{
	scenes.insert({ SceneIds::Intro, new SceneIntro() });
	scenes.insert({ SceneIds::Map0 ,new Map0() });
	scenes.insert({ SceneIds::Map1, new Map1() });
	scenes.insert({ SceneIds::Map2, new Map2() });
	scenes.insert({ SceneIds::Map3, new Map3() });
	scenes.insert({ SceneIds::Map4, new Map4() });
	scenes.insert({ SceneIds::Map5, new Map5() });
	scenes.insert({ SceneIds::MapPapyrus, new MapPapyrus() });
	scenes.insert({ SceneIds::MapSans, new MapSans() });
	scenes.insert({ SceneIds::TemMieShop, new TemMieShop() });
	
	scenes.insert({ SceneIds::Dev1 ,new SceneDev1() });
	scenes.insert({ SceneIds::MapTool ,new MapTool() });
	scenes.insert({ SceneIds::Title ,new SceneTitle() });
	scenes.insert({ SceneIds::Battle ,new SceneBattle() });
	scenes.insert({ SceneIds::Ending ,new SceneEnding() });
	
	for (auto scene : scenes)
	{
		scene.second->Init();
	}

	currentScene = startScene;
	scenes[currentScene]->Enter();
}

void SceneMgr::Release()
{
	for (auto scene : scenes)
	{
		if (scene.second->Id == currentScene)
		{
			scene.second->Exit();
		}
		scene.second->Release();
		delete scene.second;
	}
	scenes.clear();
}

void SceneMgr::ChangeScene(SceneIds id)
{
	nextScene = id;
}

void SceneMgr::Update(float dt)
{
	if (nextScene != SceneIds::None)
	{
		scenes[currentScene]->Exit();
		currentScene = nextScene;
		nextScene = SceneIds::None;
		scenes[currentScene]->Enter();
	}

	scenes[currentScene]->Update(dt);
}

void SceneMgr::Draw(sf::RenderWindow& window)
{
	scenes[currentScene]->Draw(window);
}
