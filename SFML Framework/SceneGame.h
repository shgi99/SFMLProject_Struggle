#pragma once
#include "Scene.h"

class Player;
class BackGround;
class Ground;
class Tower;
class CoinSpawner;
class SceneGame : public Scene
{
protected:
	Player* player;
	BackGround* background;
	Ground* ground;
	Tower* tower;
	CoinSpawner* coinSpawner;
	float obstacleTimer = 0.f;
	float obstacleInterval = 5.f;
	int consecutiveGaps = 0;

	int score = 0;
	int stage = 1;

	bool isGoldPatternActive = false;
public:
	SceneGame();
	~SceneGame() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void AddScore(int s);
	int GetStage() const { return stage; }
};

