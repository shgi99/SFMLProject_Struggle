#include "stdafx.h"
#include "CoinSpawner.h"
#include "Coin.h"
#include "SceneGame.h"
CoinSpawner::CoinSpawner(const std::string& name)
	: GameObject(name)
{
}

void CoinSpawner::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void CoinSpawner::SetRotation(float angle)
{
	rotation = angle;
}

void CoinSpawner::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void CoinSpawner::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void CoinSpawner::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void CoinSpawner::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 2;

	auto winSize = FRAMEWORK.GetWindowSizeF();
	for (int i = 0; i < 6; i++)
	{
		coinPosY[i] = winSize.y - 177 - 54.f * i;
	}

	std::ifstream silverFile("tables/silverpattern_table.json");
	if (silverFile.is_open())
	{
		json data;
		silverFile >> data;

		for (const auto& pattern : data["patterns"])
		{
			std::vector<int> loadedPattern;
			for (int index : pattern)
			{
				loadedPattern.push_back(index);
			}
			silverPatterns.push_back(loadedPattern);
		}
	}
	silverFile.close();

	std::ifstream goldFile("tables/goldpattern_table.json");
	if (goldFile.is_open())
	{
		json data;
		goldFile >> data;

		for (const auto& pattern : data["patterns"])
		{
			std::vector<std::vector<int>> loadedPattern;
			for (const auto& column : pattern)
			{
				std::vector<int> columnData;
				for (int heightIndex : column)
				{
					columnData.push_back(heightIndex);
				}
				loadedPattern.push_back(columnData);
			}
			goldPatterns.push_back(loadedPattern);
		}
		goldFile.close();
	}
}

void CoinSpawner::Release()
{
	for (auto coin : activeCoins)
	{
		// ReturnCoin(coin);
		sceneGame->RemoveGo(coin);
	}
	activeCoins.clear();
}

void CoinSpawner::Reset()
{
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	for (auto coin : activeCoins)
	{
		coinPool.Return(coin);
	}
	activeCoins.clear();

	spawnTimer = 0.f;
	patternSpawnTimer = 0.f;
	isGoldCoinPhase = false;
	goldCoinsCollected = 0;
	goldCoinsSize = 0;
	currentPattern.clear();
	isSilverPatternPhase = false;
	patternTimer = Utils::RandomRange(minPatternInterval, maxPatternInterval);
}

void CoinSpawner::Update(float dt)
{
	if (IsPaused())
	{
		for (auto& coin : activeCoins)
		{
			coin->SetPaused(true);
		}
		return;
	}
	if (activeCoins.size())
	{
		isGoldCoinPhase = false;
	}
	if(!isGoldCoinPhase)
	{
		patternTimer -= dt;
		if (patternTimer <= 0.f && !isSilverPatternPhase)
		{
			StartSilverCoinPattern();
			patternTimer = Utils::RandomRange(minPatternInterval, maxPatternInterval);
		}

		if (isSilverPatternPhase)
		{
			patternSpawnTimer += dt;
			if (patternSpawnTimer >= spawnInterval)
			{
				patternSpawnTimer = 0.f;
				if (currentPatternIndex < currentPattern.size())
				{
					SpawnSilverCoin();
				}
				else
				{
					isSilverPatternPhase = false;
					currentPatternIndex = 0;
				}
			}
		}
		else
		{
			spawnTimer += dt;
			if (spawnTimer >= spawnInterval)
			{
				spawnTimer = 0.f;
				SpawnSilverCoin();
			}
		}
	}
}

void CoinSpawner::Draw(sf::RenderWindow& window)
{
	for (auto coin : activeCoins)
	{
		if (coin->IsActive())
		{
			coin->Draw(window);
		}
	}
}

void CoinSpawner::SpawnSilverCoin()
{
	Coin* coin = coinPool.Take();
	if (!coin)
	{
		return;
	}

	coin->SetType(Coin::Types::Silver);
	if (isSilverPatternPhase)
	{
		float yPosition = coinPosY[currentPattern[currentPatternIndex]];
		coin->SetPosition({ FRAMEWORK.GetWindowSizeF().x + 50.f, yPosition });
		currentPatternIndex++;
	}
	else
	{
		float yPosition = coinPosY[0];
		coin->SetPosition({ FRAMEWORK.GetWindowSizeF().x + 50.f, yPosition });
	}
	activeCoins.push_back(coin);
	coin->SetActive(true);
	SCENE_MGR.GetCurrentScene()->AddGo(coin);
}

void CoinSpawner::SpawnGoldCoins(const std::vector<sf::Vector2f>& patternPositions)
{
	isGoldCoinPhase = true;
	goldCoinsCollected = 0; // 금화 수집 상태 초기화
	goldCoinsSize = patternPositions.size();
	for (const auto& position : patternPositions)
	{
		Coin* coin = coinPool.Take();
		if (!coin)
		{
			continue;
		}

		coin->SetType(Coin::Types::Gold);
		coin->SetPosition(position);
		coin->SetActive(true);
		activeCoins.push_back(coin);
		SCENE_MGR.GetCurrentScene()->AddGo(coin);
	}
}

void CoinSpawner::GrantGoldBonus()
{
	int bonus = 200;
	std::cout << "Bonus!" << std::endl;
	sceneGame->AddScore(bonus);
}

void CoinSpawner::ReturnCoin(Coin* coin)
{
	coin->SetActive(false);
	activeCoins.remove(coin);
	coinPool.Return(coin);
}

void CoinSpawner::HandleCoinCollision(Coin* coin)
{
	if (coin->GetType() == Coin::Types::Gold)
	{
		goldCoinsCollected++;
		int stage = sceneGame->GetStage();
		sceneGame->AddScore(55 - (5 * stage));
		if (goldCoinsCollected == goldCoinsSize)
		{
			GrantGoldBonus();
			isGoldCoinPhase = false;
		}
	}
	else if (coin->GetType() == Coin::Types::Silver)
	{
		sceneGame->AddScore(5);
	}

	ReturnCoin(coin);
}

void CoinSpawner::StartGoldCoinPattern()
{

	if (goldPatterns.empty())
	{
		std::cout << "No gold patterns available!" << std::endl;
		return;
	}

	// 랜덤한 금화 패턴 선택
	int patternIndex = Utils::RandomRange(0, goldPatterns.size() - 1);
	const auto& selectedPattern = goldPatterns[patternIndex];

	// 선택된 패턴의 좌표 변환
	std::vector<sf::Vector2f> patternPositions;
	for (size_t i = 0; i < selectedPattern.size(); ++i)
	{
		for (int heightIndex : selectedPattern[i])
		{
			float xPosition = FRAMEWORK.GetWindowSizeF().x + i * 60.f; // 열 간격
			float yPosition = coinPosY[heightIndex];
			patternPositions.emplace_back(xPosition, yPosition);
		}
	}

	// 금화를 생성
	SpawnGoldCoins(patternPositions);
}

void CoinSpawner::StartSilverCoinPattern()
{
	int patternIndex = Utils::RandomRange(0, silverPatterns.size() - 1);
	currentPattern = silverPatterns[patternIndex];

	isSilverPatternPhase = true;
	currentPatternIndex = 0;
}
