#pragma once
class PlungerWire;
class Ground;
class Player : public GameObject
{
public:
	enum class Status {
		Run,
		Jump,
		Wire,
		Roll,
		GameOver,
	};
protected:
	PlungerWire* plungerWire = nullptr;
	Ground* ground = nullptr;
	sf::Sprite body;
	Animator animator;

	Status state, prevState;

	std::string jumpTexId = "resource/animation/player_jump/jump.png";
	std::string wireTexId = "resource/animation/player_jump/wire.png";
	std::string rollingTexId = "resource/animation/player_jump/rolling.png";
	std::string deadTexId = "resource/player_death_animation/dead.png";

	sf::Vector2f gravity = { 0.f, 1000.f };
	float wireMin = 0.f;
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

	sf::FloatRect GetGlobalBounds() const override;
	sf::Sprite GetSprite() { return body; }
	void Init() override;
	void Release() override;
	void Reset() override;

	void HandleStateChange();
	void Update(float dt) override;
	void UpdateRun(float dt);
	void UpdateJump(float dt);
	void UpdateWire(float dt);
	void UpdateRoll(float dt);
	void Draw(sf::RenderWindow& window) override;

	void Shoot();
	void OnWireHitTower();
	void CheckGameOver();

	Status GetState() const { return state; }
};
