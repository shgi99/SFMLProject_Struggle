#pragma once
#include "Scene.h"
class UiTitle;
class SceneTitle : public Scene
{
protected:
	UiTitle* uiTitle;
public:
	SceneTitle();
	~SceneTitle() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

