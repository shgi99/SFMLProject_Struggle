#pragma once
#include "Scene.h"

class Player;
class BackGround;
class Ground;
class Tower;
class CoinSpawner;
class ScoreUI;
class UIGameOver;
class SceneGame : public Scene
{
protected:
	struct UIMessage
	{
		sf::Sprite sprite;
		Animator animator;
		bool isVisible = false; 
		float timer = 0.f;      
	};

	Player* player;
	BackGround* background;
	Ground* ground;
	Tower* tower;
	CoinSpawner* coinSpawner;
	ScoreUI* scoreUI;
	UIGameOver* uiGameOver;

	UIMessage highScoreMessage;
	UIMessage bonusMessage;
	UIMessage speedUpMessage;

	float obstacleTimer = 0.f;
	float obstacleInterval = 5.f;
	int consecutiveGaps = 0;

	int score = 0;
	int highscore = 0;
	int stage = 1;

	bool isGoldPatternActive = false;
public:
	SceneGame();
	~SceneGame() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void UpdateMessages(float dt);
	void Draw(sf::RenderWindow& window) override;

	void AddScore(int s);
	int GetStage() const { return stage; }

	void SaveHighScore(const std::string& filename);
	void LoadHighScore(const std::string& filename);

	void PlayHighScoreMessage();
	void PlayBonusMessage();
	void PlaySpeedUpMessage();

	void SceneChange(int i);
};

