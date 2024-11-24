#include "stdafx.h"
#include "UIGameOver.h"
#include "Button.h"
#include "SceneGame.h"
UIGameOver::UIGameOver(const std::string& name)
{
	button[0] = new Button("ReplayButton");
	button[1] = new Button("TutorialButton");
	button[2] = new Button("RankingButton");
}

void UIGameOver::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void UIGameOver::SetRotation(float angle)
{
	rotation = angle;
}

void UIGameOver::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
}

void UIGameOver::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void UIGameOver::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void UIGameOver::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 1;
}

void UIGameOver::Release()
{
}

void UIGameOver::Reset()
{
	background.setTexture(TEXTURE_MGR.Get("resource/graphics/gameoverUI/uibox.png"));
	Utils::SetOrigin(background, Origins::MC);
	background.setPosition(FRAMEWORK.GetWindowSizeF().x * 0.5f, 150.f);

	for (int i = 0; i < _countof(gameOverText); i++)
	{
		gameOverText[i].setTexture(TEXTURE_MGR.Get("resource/graphics/gameoverUI/gameover_UI"+ std::to_string(i + 1) + ".png"));
		Utils::SetOrigin(gameOverText[i], Origins::MC);
		gameOverText[i].setPosition(background.getPosition().x - 40.f + 110.f * i, background.getPosition().y - 70.f);
	}

	button[0]->SetType(Button::Types::Replay);
	button[1]->SetType(Button::Types::Tutorial);
	button[2]->SetType(Button::Types::Ranking);

	for (int i = 0; i < _countof(button); i++)
	{
		button[i]->Reset();
	}
	button[0]->SetPosition({ background.getPosition().x, background.getPosition().y + 30.f });

	button[1]->SetScale({ 0.8f, 0.8f });
	button[1]->SetPosition({ background.getPosition().x - 50.f, background.getPosition().y - 20.f });

	button[2]->SetScale({ 0.8f, 0.8f });
	button[2]->SetPosition({ background.getPosition().x + 50.f, background.getPosition().y - 20.f });
}

void UIGameOver::Update(float dt)
{
}

void UIGameOver::FixedUpdate(float dt)
{
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	if (sceneGame != nullptr)
	{
		sf::Vector2f mousePos = sceneGame->ScreenToUi(InputMgr::GetMousePosition());
		for (int i = 0; i < _countof(button); i++)
		{
			if (button[i]->GetGlobalBounds().contains(mousePos))
			{
				button[i]->SetTexture(true);
				if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
				{
					sceneGame->SceneChange(i);
				}
			}
			else
			{
				button[i]->SetTexture(false);
			}
		}
	}
}

void UIGameOver::Draw(sf::RenderWindow& window)
{
	window.draw(background);
	for (int i = 0; i < _countof(gameOverText); i++)
	{
		window.draw(gameOverText[i]);
	}
	for (int i = 0; i < _countof(button); i++)
	{
		button[i]->Draw(window);
	}
}
