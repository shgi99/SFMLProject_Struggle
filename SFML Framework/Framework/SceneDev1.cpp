#include "stdafx.h"
#include "SceneDev1.h"
SceneDev1::SceneDev1() : Scene(SceneIds::Dev1)
{
}

void SceneDev1::Init()
{
	Scene::Init();
}

void SceneDev1::Enter()
{
	Scene::Enter();
	worldView.setCenter(0.f, 0.f);
	worldView.setSize(FRAMEWORK.GetWindowSizeF());

	//std::ifstream f("json/example.json");
	//json data = json::parse(f);
	//std::cout << data["pi"] << ", " << data["happy"];

	//data["pi"] = 0.0;
	//std::cout << data.dump(1) << std::endl; // 들고있는 내용을 싹다 출력
}

void SceneDev1::Exit()
{
	Scene::Exit();
}

void SceneDev1::Update(float dt)
{ 
	Scene::Update(dt);
	if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
	{
		SaveDataV1 test;
		test.highScore = 123;
		
		SaveLoadMgr::Instance().SaveV1(test);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
	{
		SaveDataVC test = SaveLoadMgr::Instance().Load();
		std::cout << test.highScore;
	}
}

void SceneDev1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
