#pragma once
class Button;
class UIGameOver : public GameObject
{
protected:
	sf::Sprite background;
	sf::Sprite gameOverText[2];
	Button* button[3];
public:
	UIGameOver(const std::string& name = "");
	~UIGameOver() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};
