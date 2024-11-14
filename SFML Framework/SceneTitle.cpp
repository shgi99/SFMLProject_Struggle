#include "stdafx.h"
#include "SceneTitle.h"
#include "UiTitle.h"
SceneTitle::SceneTitle() : Scene(SceneIds::Title)
{

}

void SceneTitle::Init()
{
	uiTitle = AddGo(new UiTitle("UI Title"));
	Scene::Init();
}

void SceneTitle::Enter()
{
	Scene::Enter();
	sf::Vector2f size = FRAMEWORK.GetWindowSizeF();
	worldView.setSize(size);
	worldView.setCenter(size.x * 0.5f, size.y * 0.5f);
	uiView.setSize(size);
	uiView.setCenter(size.x * 0.5f, size.y * 0.5f);
}

void SceneTitle::Exit()
{
	Scene::Exit();
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
