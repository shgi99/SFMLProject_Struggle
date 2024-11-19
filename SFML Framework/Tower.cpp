#include "stdafx.h"
#include "Tower.h"

Tower::Tower(const std::string& name)
	: GameObject(name)
{
}

void Tower::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Tower::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Tower::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Tower::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		Utils::SetOrigin(body, originPreset);
	}
}

void Tower::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Tower::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
}

void Tower::Release()
{
}

void Tower::Reset()
{
	auto winSize = FRAMEWORK.GetWindowSizeF();
	body.setTexture(TEXTURE_MGR.Get(textureId));
	SetOrigin(Origins::BL);
	SetScale({ 1.f, 1.f });
	SetPosition({ winSize.x, winSize.y });
	SetActive(false);
}

void Tower::Update(float dt)
{
	if (!IsActive()) return;

	Move({ -moveSpeed * dt, 0.f });

	if (GetPosition().x + body.getLocalBounds().width < 0.f)
	{
		SetActive(false);
	}
}

void Tower::Draw(sf::RenderWindow& window)
{
	if (IsActive())
	{
		window.draw(body);
	}
}
