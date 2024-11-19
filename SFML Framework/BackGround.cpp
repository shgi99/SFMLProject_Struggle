#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround(const std::string& name)
	: GameObject(name)
{
}

void BackGround::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void BackGround::SetRotation(float angle)
{
	rotation = angle;
}

void BackGround::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void BackGround::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void BackGround::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void BackGround::Init()
{
	sortingLayer = SortingLayers::Background;
	sortingOrder = -1;
}

void BackGround::Release()
{
}

void BackGround::Reset()
{
	auto winSize = FRAMEWORK.GetWindowSizeF();
	background.setTexture(TEXTURE_MGR.Get(backgroundTexId));
	Utils::SetOrigin(background, Origins::TL);
	background.setPosition(0.f, 0.f);

	for (int i = 0; i < _countof(cloud); i++)
	{
		cloud[i].setTexture(TEXTURE_MGR.Get(cloudTexId));
		Utils::SetOrigin(cloud[i], Origins::TL);
	}
	cloud[0].setPosition(0.f, winSize.y - cloud[0].getLocalBounds().height - 50.f);
	cloud[1].setPosition(cloud[0].getGlobalBounds().width, winSize.y - cloud[0].getLocalBounds().height - 50.f);

	body.setTexture(TEXTURE_MGR.Get(bodyTexId));
	Utils::SetOrigin(body, Origins::BC);
	body.setPosition(winSize.x * 0.5f, winSize.y + 5.f);

	arm.setTexture(TEXTURE_MGR.Get(armTexId));
	Utils::SetOrigin(arm, Origins::BC);
	arm.setPosition(body.getPosition().x - (body.getLocalBounds().width * 0.5f) - 20.f, body.getPosition().y - body.getLocalBounds().height + 100.f);

	face.setTexture(TEXTURE_MGR.Get(idleFaceTexId));
	Utils::SetOrigin(face, Origins::BC);
	face.setPosition(body.getPosition().x + 5.f, body.getPosition().y - body.getLocalBounds().height + 30.f);

	scoreboard.setTexture(TEXTURE_MGR.Get(scoreBoardTexId));
	Utils::SetOrigin(scoreboard, Origins::BC);
	scoreboard.setPosition(arm.getPosition().x, arm.getPosition().y - arm.getLocalBounds().height + 30.f);

	moveSpeed = 200.f;
}

void BackGround::Update(float dt)
{
	for (int i = 0; i < _countof(cloud); i++)
	{
		cloud[i].move(-moveSpeed * dt, 0.f);

		if (cloud[i].getPosition().x + cloud[i].getGlobalBounds().width < 0)
		{
			cloud[i].setPosition(cloud[(i + 1) % _countof(cloud)].getPosition().x + cloud[(i + 1) % _countof(cloud)].getGlobalBounds().width,
				cloud[i].getPosition().y);
		}
	}
}

void BackGround::Draw(sf::RenderWindow& window)
{
	window.draw(background);
	for (int i = 0; i < _countof(cloud); i++)
	{
		window.draw(cloud[i]);
	}
	window.draw(body);
	window.draw(arm);
	window.draw(face);
	window.draw(scoreboard);
}

