#pragma once

class Tower : public GameObject
{
protected:
	sf::Sprite body;
	std::string textureId = "resource/graphics/Tower.png";

	float moveSpeed = 400.f;
public:
	Tower(const std::string& name = "");
	~Tower() = default;

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
