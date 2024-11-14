#include "stdafx.h"
#include "UiTitle.h"

UiTitle::UiTitle(const std::string& name)
	:GameObject(name)
{
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

	for (int i = 0; i < _countof(button); i++)
	{
		button[i].setTexture(TEXTURE_MGR.Get("resource/graphics/button1.png"));
		Utils::SetOrigin(button[i], Origins::MC);
		button[i].setPosition(400.f + 100.f * i, 400.f);
	}
}

void UiTitle::Update(float dt)
{

}

void UiTitle::FixedUpdate(float dt)
{
}

void UiTitle::Draw(sf::RenderWindow& window)
{
	window.draw(backGroundSprite);
	for (int i = 0; i < _countof(button); i++)
	{
		window.draw(button[i]);
	}
}
