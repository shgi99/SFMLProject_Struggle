#pragma once
#include "Scene.h"

class Player;
class BackGround;
class SceneGame : public Scene
{
protected:
	Player* player;
	BackGround* background;
public:
	SceneGame();
	~SceneGame() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

