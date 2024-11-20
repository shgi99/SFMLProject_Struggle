#pragma once
class Ground : public GameObject
{
protected:
	std::vector<std::pair<SpriteGo*, bool>> groundTiles;
	std::string groundTexId = "resource/graphics/ground.png";
	float moveSpeed = 400.f;

	int consecutiveGaps = 0; // 楷加 备港 俺荐
	int gapTarget = -1;       // 楷加 备港 格钎
	int tilesAfterGap = 0;

	const int minTilesAfterGap = 5;
public:
	Ground(const std::string& name = "");
	~Ground() = default;

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

	const std::vector<std::pair<SpriteGo*, bool>>& GetTiles() const { return groundTiles; }
	void RemoveTile(int index);
};
