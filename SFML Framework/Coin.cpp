#include "stdafx.h"
#include "Coin.h"
#include "Player.h"
#include "CoinSpawner.h"
Coin::Coin(const std::string& name)
	: GameObject(name)
{
}

void Coin::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Coin::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Coin::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Coin::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		Utils::SetOrigin(body, originPreset);
	}
}

void Coin::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Coin::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 2;
	moveSpeed = 400.f;
}

void Coin::Release()
{
}

void Coin::Reset()
{
	coinSpawner = dynamic_cast<CoinSpawner*>(SCENE_MGR.GetCurrentScene()->FindGo("Coin Spawner"));
	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
	SetType(type);
	SetScale({ 1.f, 1.f });
	SetOrigin(Origins::MC);
	SetActive(true);
}

void Coin::Update(float dt)
{
	if (IsPaused())
	{
		return;
	}

	Move({ -moveSpeed * dt, 0.f });

	if (GetPosition().x + GetGlobalBounds().width < 0.f)
	{
		if (coinSpawner)
		{
			coinSpawner->ReturnCoin(this);
		}
		return;
	}

	if (Utils::CheckCollision(body, player->GetSprite()))
	{
		if (player)
		{
			coinSpawner->HandleCoinCollision(this);
		}
		return;
	}
}

void Coin::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Coin::SetType(Types type)
{
	this->type = type;
	body.setTexture(TEXTURE_MGR.Get(TextureIds[(int)this->type]));
}

sf::FloatRect Coin::GetGlobalBounds() const
{
	return body.getGlobalBounds();
}
