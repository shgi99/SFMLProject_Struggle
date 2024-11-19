#pragma once

class BackGround : public GameObject
{
protected:
	sf::Sprite background;
	sf::Sprite cloud[2];

	sf::Sprite face;
	sf::Sprite body;
	sf::Sprite arm;
	sf::Sprite scoreboard;

	std::string backgroundTexId = "resource/graphics/background/background.png";
	std::string cloudTexId = "resource/graphics/background/background_cloud.png";
	std::string bodyTexId = "resource/graphics/background/body.png";
	std::string armTexId = "resource/graphics/background/arm.png";
	std::string scoreBoardTexId= "resource/graphics/background/score_board.png";

	std::string idleFaceTexId = "resource/graphics/background/idle_face.png";
	std::string deathFaceTexId = "resource/graphics/background/death_face.png";
	std::string speedUpTexId = "resource/graphics/background/speedup_face.png";

	float moveSpeed = 100.f;
public:
	BackGround(const std::string& name = "");
	~BackGround() = default;

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
};
