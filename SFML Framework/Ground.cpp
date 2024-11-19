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
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
}

void Ground::Release()
{
}

void Ground::Reset()
{
	auto winSize = FRAMEWORK.GetWindowSizeF();
	int tileCount = static_cast<int>(std::ceil(winSize.x / 150.f)) + 2;
	groundTiles.clear();
	for (int i = 0; i < tileCount; i++)
	{
		SpriteGo* tile = new SpriteGo(groundTexId, "tile");
		tile->Reset();
		tile->SetOrigin(Origins::TL);
		tile->SetPosition({ 150.f * i, winSize.y - 150.f });
		tile->SetActive(true);
		groundTiles.push_back(tile);
	}
}

void Ground::Update(float dt)
{
	for (auto& tile : groundTiles)
	{
		tile->Move({ -moveSpeed * dt, 0.f });
	}


	if (!groundTiles.empty() && groundTiles.front()->GetGlobalBounds().left + 225.f < 0.f)
	{
		SpriteGo* frontTile = groundTiles.front();
		frontTile->SetActive(true);
		frontTile->SetPosition({ groundTiles.back()->GetPosition().x + 150.f , frontTile->GetPosition().y });
		groundTiles.erase(groundTiles.begin());
		groundTiles.push_back(frontTile);
	}
} 

void Ground::Draw(sf::RenderWindow& window)
{
	for (const auto& tile : groundTiles)
	{
		if (tile->IsActive())
		{
			tile->Draw(window);
		}
	}
}

void Ground::RemoveTile(int index)
{
	if (index >= 0 && index < groundTiles.size())
	{
		groundTiles[index]->SetActive(false);
	}
}
