#pragma once
class PlungerWire;
class Player : public GameObject
{
public:
	enum class Status {
		Run,
		Jump,
		Wire,
		Roll,
	};
protected:
	PlungerWire* plungerWire = nullptr;

	sf::Sprite body;
	Animator animator;
	Status state;

	std::string jumpTexId = "resource/animation/player_jump/jump.png";
	std::string wireTexId = "resource/animation/player_jump/wire.png";
	std::string rollingTexId = "resource/animation/player_jump/rolling.png";

	sf::Vector2f gravity = { 0.f, 1000.f };
	sf::Vector2f velocity = { 0.f, 0.f };
	bool isGrounded = true;
public:
	Player(const std::string& name = "");
	~Player() = default;

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

	void Shoot();
};
