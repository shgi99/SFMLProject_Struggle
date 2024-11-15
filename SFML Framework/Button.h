#pragma once

class Button : public GameObject
{
public:
	enum class Types
	{
		Play,
		Replay,
		Tutorial,
		Ranking,
	};
protected:
	Types types = Types::Play;

	sf::Sprite button;
	std::string buttonTexId;
	sf::Sprite text;
	std::string textTexId;

	std::string nonClickButtonId = "resource/graphics/button1.png";
	std::string clickButtonId = "resource/graphics/button2.png";
public:
	Button(const std::string& name = "");
	~Button() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	sf::FloatRect GetGlobalBounds() const { return button.getGlobalBounds(); }
	void SetTexture(bool isCollision);

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetType(Types type);
};
