#include "stdafx.h"
#include "PlungerWire.h"

PlungerWire::PlungerWire(const std::string& name)
	: GameObject(name)
{
}

void PlungerWire::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void PlungerWire::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void PlungerWire::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void PlungerWire::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void PlungerWire::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

sf::FloatRect PlungerWire::GetLocalBounds() const
{
	return body.getLocalBounds();
}

void PlungerWire::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
}

void PlungerWire::Release()
{
}

void PlungerWire::Reset()
{
	body.setTexture(TEXTURE_MGR.Get(textureId));
	speed = 1500.f;
	SetOrigin(Origins::ML);
	SetPosition({ 0.f, 0.f });
	SetRotation(0.f);
	SetScale({ 1.f, 1.f });
}

void PlungerWire::Update(float dt)
{
	position += direction * speed * dt;
	SetPosition(position);
	hitBox.UpdateTr(body, GetLocalBounds());

	if (position.y < -50.f)
	{
		SetActive(false);
	}
}

void PlungerWire::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);
}

void PlungerWire::Fire(const sf::Vector2f& pos, const sf::Vector2f& dir)
{
	SetPosition(pos);
	direction = dir;

	SetRotation(Utils::Angle(direction));
}
