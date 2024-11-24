#include "stdafx.h"
#include "SceneGame.h"
#include "Player.h"
#include "BackGround.h"
#include "Ground.h"
#include "Tower.h"
#include "CoinSpawner.h"
#include "ScoreUI.h"
#include "UIGameOver.h"
SceneGame::SceneGame() : Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	coinSpawner = AddGo(new CoinSpawner("Coin Spawner"));
	player = AddGo(new Player("Player"));
	background = AddGo(new BackGround("BackGround"));
	ground = AddGo(new Ground("Ground"));
	tower = AddGo(new Tower("Tower"));
	scoreUI = AddGo(new ScoreUI("Score UI"));
	uiGameOver = AddGo(new UIGameOver("UI GameOver"));

	highScoreMessage.sprite.setPosition({ 200.f, FRAMEWORK.GetWindowSizeF().y - 100.f });
	highScoreMessage.sprite.setScale(1.f, 1.f);
	Utils::SetOrigin(highScoreMessage.sprite, Origins::TL);
	bonusMessage.sprite.setPosition({ 200.f, FRAMEWORK.GetWindowSizeF().y * 0.5f });
	bonusMessage.sprite.setScale(1.f, 1.f);
	Utils::SetOrigin(bonusMessage.sprite, Origins::TL);
	speedUpMessage.sprite.setPosition({ 200.f, FRAMEWORK.GetWindowSizeF().y + 100.f });
	speedUpMessage.sprite.setScale(1.f, 1.f);
	Utils::SetOrigin(speedUpMessage.sprite, Origins::TL);
	Scene::Init();
}

void SceneGame::Enter()
{
	sf::Vector2f size = FRAMEWORK.GetWindowSizeF();
	worldView.setSize(size);
	worldView.setCenter(size.x * 0.5f, size.y * 0.5f);
	uiView.setSize(size);
	uiView.setCenter(size * 0.5f);
	obstacleTimer = 0.f;
	consecutiveGaps = 0;
	score = 0;
	stage = 1;
	isGoldPatternActive = false;

	Scene::Enter();
	LoadHighScore("highscore.txt");

	highScoreMessage.animator.SetTarget(&highScoreMessage.sprite);
	bonusMessage.animator.SetTarget(&bonusMessage.sprite);
	speedUpMessage.animator.SetTarget(&speedUpMessage.sprite);
	ground->SetPaused(false);
	tower->SetPaused(false);
	coinSpawner->SetPaused(false);
	uiGameOver->SetActive(false);
}

void SceneGame::Exit()
{
	coinSpawner->Reset();
	SaveHighScore("highscore.txt");
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);

	if (player->GetState() == Player::Status::GameOver)
	{
		ground->SetPaused(true);
		tower->SetPaused(true);
		coinSpawner->SetPaused(true);
		uiGameOver->SetActive(true);
		return;
	}
	UpdateMessages(dt);
	if (tower->IsActive() && !isGoldPatternActive)
	{
		coinSpawner->StartGoldCoinPattern();
		isGoldPatternActive = true;
	}
	else if (!tower->IsActive() && isGoldPatternActive)
	{
		isGoldPatternActive = false; 
	}
}

void SceneGame::UpdateMessages(float dt)
{
	auto updateMessage = [dt](UIMessage& message, float duration) {
		if (message.isVisible)
		{
			message.timer += dt;
			message.animator.Update(dt);

			if (message.timer >= duration)
			{
				message.isVisible = false;
			}
		}
		};

	updateMessage(highScoreMessage, 2.f); // 최고점수 메시지 2초 표시
	updateMessage(bonusMessage, 2.f);    // 보너스 메시지 2초 표시
	updateMessage(speedUpMessage, 2.f);  // 속도 증가 메시지 2초 표시
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	if (highScoreMessage.isVisible)
	{
		window.draw(highScoreMessage.sprite);
	}
	if (bonusMessage.isVisible)
	{
		window.draw(bonusMessage.sprite);
	}
	if (speedUpMessage.isVisible)
	{
		window.draw(speedUpMessage.sprite);
	}
}

void SceneGame::AddScore(int s)
{
	score += s;
	scoreUI->UpdateScore(score);
	if (highscore <= score)
	{
		highscore = score;
		background->SetHighScore(highscore);
	}
}

void SceneGame::SaveHighScore(const std::string& filename)
{
	std::ofstream outFile(filename);

	if (!outFile) {
		std::cerr << "파일을 열 수 없습니다." << std::endl;
		return;
	}
	outFile << highscore;
	outFile.close();

	return;
}

void SceneGame::LoadHighScore(const std::string& filename)
{
	std::ifstream inFile(filename);

	if (!inFile) {
		std::cerr << "파일을 열 수 없습니다." << std::endl;
		return;
	}

	inFile >> highscore;
	
	background->SetHighScore(highscore);

	inFile.close();
	return;
}

void SceneGame::PlayHighScoreMessage()
{
	highScoreMessage.animator.Play("animations/best_anim.json");
	highScoreMessage.isVisible = true;
	highScoreMessage.timer = 0.f;     
}

void SceneGame::PlayBonusMessage()
{
	bonusMessage.animator.Play("animations/bonus_anim.json");
	bonusMessage.isVisible = true; // 활성화
	bonusMessage.timer = 0.f;     // 타이머 초기화
}

void SceneGame::PlaySpeedUpMessage()
{
	speedUpMessage.animator.Play("animations/speedup_anim.json");
	speedUpMessage.isVisible = true;
	speedUpMessage.timer = 0.f;     
}

void SceneGame::SceneChange(int i)
{
	if (i == 0)
	{
		Exit();
		SCENE_MGR.ChangeScene(SceneIds::Game);
	}
}


