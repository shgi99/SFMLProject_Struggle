#pragma once

class SpriteGo : public GameObject
{
protected:
	sf::Sprite sprite;
	std::string textureId;

public:
	SpriteGo(const std::string& texId = "", const std::string& name = "");
	~SpriteGo() = default;

	void SetTextureId(const std::string& id) { textureId = id; }

	void SetOrigin(Origins preset);
	void SetOrigin(const sf::Vector2f& newOrigin);

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& pos) override;

	sf::FloatRect GetLocalBounds() const override
	{
		return sprite.getLocalBounds();
	}
	sf::FloatRect GetGlobalBounds() const override
	{
		return sprite.getGlobalBounds();
	}

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

