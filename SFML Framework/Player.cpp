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
	SetPosition({ winSize.x * 0.3f, winSize.y * 0.7f });
	SetScale({ 1.f, 1.f });
	SetOrigin(Origins::BC);
	state = Status::Run;
	isGrounded = true;
	velocity = { 0.f, 0.f }; 
	gravity = { 0.f, 980.f }; 

	animator.Play("animations/player_anim.json");
}

void Player::Update(float dt)
{
	animator.Update(dt);
	hitBox.UpdateTr(body, body.getGlobalBounds());

	auto& groundTiles = ground->GetTiles();
	for (const auto& tile : groundTiles)
	{

		if (!tile->IsActive()) // 비활성화된 타일은 무시
			continue;

		sf::FloatRect tileBounds = tile->GetGlobalBounds();
		if (velocity.y > 0.f && tileBounds.contains(position.x, position.y))
		{
			velocity.y = 0.f;
			position.y = tileBounds.top;
			if(state != Status::Run)
				animator.Play("animations/player_anim.json");
			state = Status::Run;
			isGrounded = true;
			break;
		}
	}

	if (position.y > groundTiles.front()->GetPosition().y + 30.f && state == Status::Run)
	{
		std::cout << "Game Over!" << std::endl;
		return;
	}

	if (state == Status::Jump && InputMgr::GetMouseButtonDown(sf::Mouse::Right))
	{
		Shoot();
	}

	if (isGrounded && InputMgr::GetMouseButtonDown(sf::Mouse::Right))
	{
		isGrounded = false;
		state = Status::Jump;
		velocity.y = -450.f;
		animator.Stop();
		body.setTexture(TEXTURE_MGR.Get(jumpTexId));
	}

	velocity += gravity * dt;
	if (velocity.y > 0.f) 
	{
		velocity.y += 350.f * dt; 
	}
	position += velocity * dt;

	SetPosition(position);
	if (state == Status::Roll)
	{
		SetRotation(rotation + 30.f * dt);
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

