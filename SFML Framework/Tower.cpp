#include "stdafx.h"
#include "Tower.h"
#include "Ground.h"
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
	ground = dynamic_cast<Ground*>(SCENE_MGR.GetCurrentScene()->FindGo("Ground"));
	auto winSize = FRAMEWORK.GetWindowSizeF();
	body.setTexture(TEXTURE_MGR.Get(textureId));
	SetOrigin(Origins::BL);
	SetScale({ 1.f, 1.f });
	SetPosition({ winSize.x + 50.f, winSize.y });
	SetActive(false);
	consecutiveGaps = 0;
}

void Tower::Update(float dt)
{
	if (isPaused)
	{
		return;
	}
	hitBox.UpdateTr(body, GetTopBounds());
	if (IsActive()) {
		Move({ -moveSpeed * dt, 0.f });

		if (GetPosition().x + body.getLocalBounds().width < 0.f)
		{
			SetActive(false);
			consecutiveGaps = 0;
		}

		return;
	}
}

void Tower::UpdateInactive(float dt)
{
	auto& tiles = ground->GetTiles();
	for (const auto& pair : tiles)
	{
		if (pair.second)
		{
			consecutiveGaps++;
			if (consecutiveGaps >= 3)
			{
				if (!tiles.empty())
				{
					SetPosition({ pair.first->GetPosition().x - 150.f, FRAMEWORK.GetWindowSizeF().y});
					SetActive(true);
					break;
				}
			}
		}
		else
		{
			consecutiveGaps = 0;
		}
	}
}


void Tower::Draw(sf::RenderWindow& window)
{
	if (IsActive())
	{
		window.draw(body);
		hitBox.Draw(window);
	}
}

sf::FloatRect Tower::GetTopBounds() const
{
	return { body.getPosition().x, body.getPosition().y - body.getGlobalBounds().height,
	body.getGlobalBounds().width, body.getGlobalBounds().height * 0.3f };
}
