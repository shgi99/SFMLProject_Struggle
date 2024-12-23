#pragma once
class Button;
class UiTitle : public GameObject
{
protected:
	sf::Sprite backGroundSprite;
	Button* button[2];
public:
	UiTitle(const std::string& name = "");
	~UiTitle() = default;

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
