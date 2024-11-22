#pragma once
class CoinSpawner;
class Player;
class Coin : public GameObject
{
public:
	enum class Types
	{
		Silver,
		Gold,
	};
protected:
	Types type;
	sf::Sprite body;

	std::string TextureIds[2] = {"resource/graphics/silvercoin.png", "resource/graphics/goldcoin.png"};
	float moveSpeed = 400.f;

	CoinSpawner* coinSpawner = nullptr;
	Player* player = nullptr;
public:
	Coin(const std::string& name = "");
	~Coin() = default;

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

	void SetType(Types type);

	Types GetType() const { return type; }
	sf::FloatRect GetGlobalBounds() const override;
};
