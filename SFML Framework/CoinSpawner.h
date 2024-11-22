#pragma once
class Coin;
class SceneGame;
class CoinSpawner : public GameObject
{
protected:
	SceneGame* sceneGame = nullptr;

	ObjectPool<Coin> coinPool;
	std::list<Coin*> activeCoins;
	// 은화 관련
	std::vector<std::vector<int>> silverPatterns;
	std::vector<int> currentPattern;
	int currentPatternIndex = 0;
	bool isSilverPatternPhase = false;
	float patternSpawnTimer = 0.f;
	float patternTimer = 0.f;
	float spawnTimer = 0.f;
	const float spawnInterval = 0.1f; 
	const float minPatternInterval = 2.f;
	const float maxPatternInterval = 5.f;
	float coinPosY[6]; 

	// 금화 관련
	bool isGoldCoinPhase = false;
	std::vector<std::vector<std::vector<int>>> goldPatterns;
	int goldCoinsCollected = 0;
	int goldCoinsSize = 0;
public:
	CoinSpawner(const std::string& name = "");
	~CoinSpawner() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SpawnSilverCoin();
	void SpawnGoldCoins(const std::vector<sf::Vector2f>& patternPositions);
	void GrantGoldBonus();

	void ReturnCoin(Coin* coin);
	void HandleCoinCollision(Coin* coin);
	void StartGoldCoinPattern();
	void StartSilverCoinPattern();

};
