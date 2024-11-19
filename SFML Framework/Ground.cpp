#include "stdafx.h"
#include "Ground.h"

Ground::Ground(const std::string& name)
	: GameObject(name)
{
}

void Ground::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void Ground::SetRotation(float angle)
{
	rotation = angle;
}

void Ground::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void Ground::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void Ground::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void Ground::Init()
{
}

void Ground::Release()
{
}

void Ground::Reset()
{
}

void Ground::Update(float dt)
{
}

void Ground::Draw(sf::RenderWindow& window)
{
}
