#include "stdafx.h"
#include "SceneGame.h"
#include "Player.h"
#include "BackGround.h"
#include "Ground.h"
#include "Tower.h"
SceneGame::SceneGame() : Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	player = AddGo(new Player("Player"));
	background = AddGo(new BackGround("BackGround"));
	ground = AddGo(new Ground("Ground"));
	tower = AddGo(new Tower("Tower"));
	Scene::Init();
}

void SceneGame::Enter()
{
	sf::Vector2f size = FRAMEWORK.GetWindowSizeF();
	worldView.setSize(size);
	worldView.setCenter(size.x * 0.5f, size.y * 0.5f);
	uiView.setSize(size);
	uiView.setCenter(size * 0.5f);
	obstacleTimer = 0.f;
	consecutiveGaps = 0;
	Scene::Enter();
}

void SceneGame::Exit()
{
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);

}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}


