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

	for (int i = 0; i < 10; i++)
	{
		digitTextures[i].setTexture(TEXTURE_MGR.Get("resource/graphics/highscore_sprite/highscore_sprite (" + std::to_string(i + 1) + ").png"));
		Utils::SetOrigin(digitTextures[i], Origins::TL);
	}

	moveSpeed = 200.f;
	SetHighScore(highScore);
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

	for (auto& digit : highScoreDigits)
	{
		window.draw(digit);
	}
}

void BackGround::SetHighScore(int score)
{
	highScore = score;


	std::string scoreStr = std::to_string(highScore);
	while (scoreStr.size() < 7)
	{
		scoreStr = "0" + scoreStr;
	}

	highScoreDigits[0].setPosition(scoreboard.getPosition().x - 60.f, scoreboard.getPosition().y - 65.f);
	float xOffset = highScoreDigits[0].getPosition().x;

	for (int i = 0; i < scoreStr.size(); ++i)
	{
		int digitValue = scoreStr[i] - '0'; // ASCII 값 변환
		highScoreDigits[i] = digitTextures[digitValue];
		highScoreDigits[i].setPosition(xOffset + i * (highScoreDigits[i].getLocalBounds().width - 15.f), scoreboard.getPosition().y - 65.f);
		highScoreDigits[i].setScale(1.f, 1.f); // 적절한 스케일 조정
	}
}

