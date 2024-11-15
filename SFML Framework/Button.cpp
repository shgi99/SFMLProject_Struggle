#include "stdafx.h"
#include "Button.h"

Button::Button(const std::string& name)
	: GameObject(name)
{
}

void Button::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	button.setPosition(position);
	text.setPosition(position);
}

void Button::SetRotation(float angle)
{
	rotation = angle;
	button.setRotation(rotation);
	text.setRotation(rotation);
}

void Button::SetScale(const sf::Vector2f& s)
{
	scale = s;
	button.setScale(scale);
	text.setScale(scale);
}

void Button::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(button, originPreset);
		origin = Utils::SetOrigin(text, originPreset);
	}
}

void Button::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	button.setOrigin(origin);
	text.setOrigin(origin);
}

void Button::SetTexture(bool isCollision)
{
	if (!isCollision)
	{
		button.setTexture(TEXTURE_MGR.Get(nonClickButtonId));
	}
	else
	{
		button.setTexture(TEXTURE_MGR.Get(clickButtonId));
	}
}

void Button::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;
}

void Button::Release()
{
}

void Button::Reset()
{
	button.setTexture(TEXTURE_MGR.Get(nonClickButtonId));
	SetOrigin(Origins::MC);
	SetType(types);
	SetPosition({ 0.f, 0.f });
	SetRotation(0.f);
	SetScale({ 1.f, 1.f });
}

void Button::Update(float dt)
{
}

void Button::Draw(sf::RenderWindow& window)
{
	window.draw(button);
	window.draw(text);
}

void Button::SetType(Types type)
{
	types = type;
	switch (types)
	{
	case Types::Play:
		textTexId = "resource/graphics/gamestartUI_text.png";
		break;
	case Types::Replay:
		textTexId = "resource/graphics/gameoverUI/replayUI_text.png";
		break;
	case Types::Tutorial:
		textTexId = "resource/graphics/gameoverUI/tutorialUI_text.png";
		break;
	case Types::Ranking:
		textTexId = "resource/graphics/gameoverUI/rankingUI_text.png";
		break;
	}

	text.setTexture(TEXTURE_MGR.Get(textTexId), true);
}
