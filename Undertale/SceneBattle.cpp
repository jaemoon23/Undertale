#include "stdafx.h"
#include "SceneBattle.h"

SceneBattle::SceneBattle()
	: Scene(SceneIds::Battle)
{
}

void SceneBattle::Init()
{
	Scene::Init();
}

void SceneBattle::Enter()
{
	Scene::Enter();
}

void SceneBattle::Exit()
{
	Scene::Exit();
}

void SceneBattle::Update(float dt)
{
	Scene::Update(dt);
}

void SceneBattle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}