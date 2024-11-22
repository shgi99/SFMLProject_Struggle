#include "stdafx.h"
#include "Player.h"
#include "PlungerWire.h"
#include "Ground.h"
Player::Player(const std::string& name)
	: GameObject(name)
{
}

void Player::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Player::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Player::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Player::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		Utils::SetOrigin(body, originPreset);
	}
}

void Player::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Player::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 2;

	animator.SetTarget(&body);
	animator.Play("animations/player_anim.json");
	Variables::isDrawHitBox = true;
}

void Player::Release()
{
}

void Player::Reset()
{
	ground = dynamic_cast<Ground*>(SCENE_MGR.GetCurrentScene()->FindGo("Ground"));
	sf::Vector2f winSize = FRAMEWORK.GetWindowSizeF();
	SetPosition({ winSize.x * 0.3f, winSize.y * 0.8f });
	SetScale({ 1.f, 1.f });
	SetOrigin(Origins::BC);
	state = Status::Run;
	prevState = Status::Run;
	isGrounded = false;
	velocity = { 0.f, 0.f }; 
	gravity = { 0.f, 2500.f }; 
	wireMin = GetPosition().y + 50.f;
	animator.Play("animations/player_anim.json");
}

void Player::HandleStateChange()
{
	switch (state)
	{
	case Status::Run:
		animator.Play("animations/player_anim.json");
		SetRotation(0.f);
		break;
	case Status::Jump:
		animator.Stop();
		body.setTexture(TEXTURE_MGR.Get(jumpTexId));
		break;
	case Status::Wire:
		animator.Stop();
		body.setTexture(TEXTURE_MGR.Get(wireTexId));
		break;
	case Status::Roll:
		animator.Stop();
		body.setTexture(TEXTURE_MGR.Get(rollingTexId));
		break;
	}
}

void Player::Update(float dt)
{
	if (state == Status::GameOver)
	{
		animator.Stop();
		body.setTexture(TEXTURE_MGR.Get(deadTexId));
		return;
	}
	animator.Update(dt);
	hitBox.UpdateTr(body, body.getGlobalBounds());

	switch (state)
	{
	case Status::Run:
		UpdateRun(dt);
		break;
	case Status::Jump:
		UpdateJump(dt);
		break;
	case Status::Wire:
		UpdateWire(dt);
		break;
	case Status::Roll:
		UpdateRoll(dt);
		break;
	}

	if (prevState != state)
	{
		HandleStateChange();
		prevState = state;
	}
	CheckGameOver();
	SetPosition(position);
}

void Player::UpdateRun(float dt)
{
	isGrounded = false;
	auto& groundTiles = ground->GetTiles();
	for (const auto& tile : groundTiles)
	{
		if (!tile.first->IsActive()) continue;
		SetRotation(0.f);
		sf::FloatRect tileBounds = tile.first->GetGlobalBounds();
		if (velocity.y >= 0.f && tileBounds.contains(position.x, position.y))
		{
			velocity.y = 0.f;
			position.y = tileBounds.top;
			isGrounded = true;
		}
	}

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Right))
	{
		isGrounded = false;
		state = Status::Jump;
		velocity.y = -700.f;
	}
	velocity.y += gravity.y * dt;
	position.y += velocity.y * dt;
}

void Player::UpdateJump(float dt)
{
	velocity.y += gravity.y * dt;
	position += velocity * dt;

	auto& groundTiles = ground->GetTiles();
	for (const auto& tile : groundTiles)
	{
		if (!tile.first->IsActive()) continue;

		sf::FloatRect tileBounds = tile.first->GetGlobalBounds();
		if (velocity.y > 0.f && tileBounds.contains(position.x, position.y))
		{
			velocity.y = 0.f;
			position.y = tileBounds.top;
			state = Status::Run;
			isGrounded = true;
			return;
		}
	}

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Right))
	{
		Shoot(); // 와이어 발사
	}
}


void Player::UpdateWire(float dt)
{
	body.setTexture(TEXTURE_MGR.Get(wireTexId));
	velocity.y += gravity.y * dt;
	position.y += velocity.y * dt;

	if (position.y > wireMin)
	{
		velocity.y = -1500.f; // 위로 상승
	}
	else if (position.y < plungerWire->GetPosition().y)
	{
		velocity.y = -500.f; // 아래로 하강
		state = Status::Roll;
	}
}


void Player::UpdateRoll(float dt)
{
	body.setTexture(TEXTURE_MGR.Get(rollingTexId));
	SetRotation(rotation + 1.f);
	velocity.y += gravity.y * dt;
	position.y += velocity.y * dt;

	if (position.y > wireMin)
	{
		if(plungerWire != nullptr)
		{
			SCENE_MGR.GetCurrentScene()->RemoveGo(plungerWire);
			plungerWire = nullptr;
		}
		state = Status::Run;
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);

	if (plungerWire != nullptr && plungerWire->IsActive())
	{
		// 와이어 선 추가
		sf::VertexArray wireLine(sf::Lines, 2);
		wireLine[0].position = { position.x + body.getLocalBounds().width * 0.5f - 10.f,  position.y - body.getLocalBounds().height + 15.f }; // 선의 시작점 (플레이어)
		wireLine[0].color = sf::Color::White;                // 선 색상
		wireLine[1].position = plungerWire->GetPosition();   // 선의 끝점 (뚫어뻥)
		wireLine[1].color = sf::Color::White;

		window.draw(wireLine);   // 와이어 선 그리기
	}
}

void Player::Shoot()
{
	if (plungerWire != nullptr && plungerWire->IsActive())
	{
		return;
	}

	if (plungerWire == nullptr)
	{
		plungerWire = new PlungerWire("PlungerWire");
		plungerWire->Reset();
		SCENE_MGR.GetCurrentScene()->AddGo(plungerWire);
	}

	sf::Vector2f startPosition = body.getPosition();
	sf::Vector2f targetPosition = { 480.f, 0.f };
	sf::Vector2f direction = Utils::GetNormal(targetPosition - startPosition);

	plungerWire->Fire(startPosition, direction);
	plungerWire->SetActive(true);
}

void Player::OnWireHitTower()
{
	state = Status::Wire;

}

void Player::CheckGameOver()
{
	sf::Vector2f winSize = FRAMEWORK.GetWindowSizeF();

	if (state == Status::Run)
	{
		if (!isGrounded)
		{
			state = Status::GameOver;
		}
	}
	else if ((state == Status::Jump || state == Status::Roll || state == Status::Wire) && position.y >= winSize.y)
	{
		state = Status::GameOver;
	}
}

