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
	player->SetActive(true);
	background = AddGo(new BackGround("BackGround"));
	background->SetActive(true);
	ground = AddGo(new Ground("Ground"));
	ground->SetActive(true);
	tower = AddGo(new Tower("Tower"));
	Scene::Init();
}

void SceneGame::Enter()
{
	Scene::Enter();
	sf::Vector2f size = FRAMEWORK.GetWindowSizeF();
	worldView.setSize(size);
	worldView.setCenter(size.x * 0.5f, size.y * 0.5f);
	uiView.setSize(size);
	uiView.setCenter(size * 0.5f);
	obstacleTimer = 0.f;
}

void SceneGame::Exit()
{
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);

	obstacleTimer += dt;

	if (obstacleTimer >= obstacleInterval)
	{
		obstacleTimer = 0.f;

		if (!ground->GetTiles().empty())
		{
			tower->Reset();
			tower->SetActive(true);
			ground->RemoveTile(ground->GetTiles().size() - 1);
		}
	}
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}


