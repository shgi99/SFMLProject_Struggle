#pragma once

class ScoreUI : public GameObject
{
protected:
	sf::Sprite coinSprite;
	sf::Sprite scoreSprite[10];
	std::vector<sf::Sprite> digitSprites;

	int currentScore = 0;

	std::string coinTexId = "resource/graphics/score_sprite/score_icon.png";
public:
	ScoreUI(const std::string& name = "");
	~ScoreUI() = default;

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

	void UpdateScore(int score);
};
