#include "stdafx.h"
#include "UiTitle.h"
#include "Button.h"
#include "SceneTitle.h"
UiTitle::UiTitle(const std::string& name)
	:GameObject(name)
{
	button[0] = new Button("PlayButton");
	button[1] = new Button("TutorialButton");
}

void UiTitle::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void UiTitle::SetRotation(float angle)
{
	rotation = angle;
}

void UiTitle::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
}

void UiTitle::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void UiTitle::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void UiTitle::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 1;

}

void UiTitle::Release()
{
}

void UiTitle::Reset()
{
	backGroundSprite.setTexture(TEXTURE_MGR.Get("resource/graphics/Main.png"));
	Utils::SetOrigin(backGroundSprite, Origins::TL);
	backGroundSprite.setPosition(0.f, 0.f);
	
	button[0]->SetType(Button::Types::Play);
	button[1]->SetType(Button::Types::Tutorial);

	for (int i = 0; i < _countof(button); i++)
	{
		button[i]->Reset();
		button[i]->SetPosition({ 420.f + 100.f * i, 370.f });
	}
}

void UiTitle::Update(float dt)
{
}

void UiTitle::FixedUpdate(float dt)
{
	SceneTitle* sceneTitle = dynamic_cast<SceneTitle*>(SCENE_MGR.GetCurrentScene());
	if (sceneTitle != nullptr)
	{
		sf::Vector2f mousePos = sceneTitle->ScreenToUi(InputMgr::GetMousePosition());
		for (int i = 0; i < _countof(button); i++)
		{
			if (button[i]->GetGlobalBounds().contains(mousePos))
			{
				button[i]->SetTexture(true);
				if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
				{
					sceneTitle->SceneChange(i);
				}
			}
			else
			{
				button[i]->SetTexture(false);
			}
		}
	}
}

void UiTitle::Draw(sf::RenderWindow& window)
{
	window.draw(backGroundSprite);
	for (int i = 0; i < _countof(button); i++)
	{
		button[i]->Draw(window);
	}
}
