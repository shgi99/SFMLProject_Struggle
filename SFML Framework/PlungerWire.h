#pragma once
class Player;
class Tower;
class PlungerWire : public GameObject
{
protected:
	sf::Sprite body;
	std::string textureId = "resource/graphics/Plunger.png";

	sf::Vector2f direction;
	float speed = 0.f;

	Player* player = nullptr;
	Tower* tower = nullptr;

	bool isAttached = false;
public:
	PlungerWire(const std::string& name = "");
	~PlungerWire() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;
	sf::FloatRect GetLocalBounds() const;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void Fire(const sf::Vector2f& pos, const sf::Vector2f& dir);
};
