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
	for (auto& pair : groundTiles)
	{
		delete pair.first;
	}
	groundTiles.clear();
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
		groundTiles.push_back({ tile, false });
	}

	gapTarget = -1;
	consecutiveGaps = 0;
	tilesAfterGap = 0;
}

void Ground::Update(float dt)
{

	for (auto& pair : groundTiles)
	{
		pair.first->Move({ -moveSpeed * dt, 0.f });
	}


	if (!groundTiles.empty() && groundTiles.front().first->GetGlobalBounds().left + 225.f < 0.f)
	{
		auto& frontTile = groundTiles.front();
		SpriteGo* tile = frontTile.first;
		bool isGap = frontTile.second;

		tile->SetActive(true); 
		isGap = false;

		// 备港 菩畔 汲沥
		if (gapTarget == -1 && tilesAfterGap >= minTilesAfterGap)
		{
			gapTarget = rand() % 3 + 1; 
			consecutiveGaps = 0;
			tilesAfterGap = 0;
		}

		// 备港 积己
		if (consecutiveGaps < gapTarget)
		{
			isGap = true;
			tile->SetActive(false);
			consecutiveGaps++;
		}
		else 
		{
			gapTarget = -1;
			tilesAfterGap++;
			isGap = false;
		}

		tile->SetPosition({ groundTiles.back().first->GetPosition().x + 150.f, tile->GetPosition().y });
		groundTiles.erase(groundTiles.begin());
		std::cout << isGap << std::endl;
		groundTiles.push_back({tile, isGap });
	}
} 

void Ground::Draw(sf::RenderWindow& window)
{
	for (const auto& pair : groundTiles)
	{
		if (pair.first->IsActive())
		{
			pair.first->Draw(window);
		}
	}
}

void Ground::RemoveTile(int index)
{
	if (index >= 0 && index < groundTiles.size())
	{
		groundTiles[index].first->SetActive(false);
		groundTiles[index].second = true;
	}
}
