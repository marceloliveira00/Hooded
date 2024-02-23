#pragma once

#include "../Headers/WindowManager.hpp"
#include "../Headers/MapManager.hpp"
#include "../Headers/Hooded.hpp"
#include "../Headers/Enums/Level.hpp"

class GameManager
{
public:
	GameManager();
	~GameManager();

	void Render();
	const bool Running() const;
	void Update();

private:
	sf::Clock m_clock;
	float m_deltaTime = 0.f;

	MapManager* m_mapManager;
	Hooded* m_hooded;

	WindowManager* m_windowManager;
};

