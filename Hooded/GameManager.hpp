#pragma once

#include "WindowManager.hpp"
#include "Hooded.hpp"

class GameManager
{
public:
	sf::Clock clock;
	float deltaTime = 0.f;

	GameManager();
	~GameManager();

	void Render();
	const bool Running() const;
	void Update();

private:
	Hooded* hooded;
	WindowManager* windowManager;
};

