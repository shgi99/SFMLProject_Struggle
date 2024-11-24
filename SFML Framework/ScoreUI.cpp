#include "stdafx.h"
#include "ScoreUI.h"

ScoreUI::ScoreUI(const std::string& name)
{
}

void ScoreUI::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void ScoreUI::SetRotation(float angle)
{
	rotation = angle;
}

void ScoreUI::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
}

void ScoreUI::SetOrigin(Origins preset)
{
}

void ScoreUI::SetOrigin(const sf::Vector2f& newOrigin)
{
}

void ScoreUI::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;
}

void ScoreUI::Release()
{
	digitSprites.clear();
}

void ScoreUI::Reset()
{
	coinSprite.setTexture(TEXTURE_MGR.Get(coinTexId));
	for (int i = 0; i < 10; i++)
	{
		scoreSprite[i].setTexture(TEXTURE_MGR.Get("resource/graphics/score_sprite/score_sprite" + std::to_string(i) + ".png"));
	}
	digitSprites.clear();
	currentScore = 0;
	UpdateScore(currentScore);

	Utils::SetOrigin(coinSprite, Origins::TL);
	coinSprite.setScale(1.f, 1.f);
	coinSprite.setPosition(10.f, 10.f);


}

void ScoreUI::Update(float dt)
{
}

void ScoreUI::Draw(sf::RenderWindow& window)
{
	window.draw(coinSprite);
	for (auto& digit : digitSprites)
	{
		window.draw(digit);
	}
}

void ScoreUI::UpdateScore(int score)
{
	currentScore = score;

	// 숫자 스프라이트 갱신
	digitSprites.clear();
	std::string scoreStr = std::to_string(currentScore);
	float xOffset = coinSprite.getPosition().x + coinSprite.getLocalBounds().width + 10.f;

	for (char ch : scoreStr)
	{
		int digitValue = ch - '0'; // ASCII 값을 숫자로 변환
		if (digitValue < 0 || digitValue > 9) continue;

		sf::Sprite digit = scoreSprite[digitValue];
		digit.setPosition(position.x + xOffset, 10.f);
		digit.setScale(1.f, 1.f);
		digitSprites.push_back(digit);

		xOffset += digit.getLocalBounds().width - 10.f;
	}
}
