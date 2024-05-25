#pragma once

#include "../Headers/WindowManager.hpp"
#include "../Headers/BackgroundManager.hpp"
#include "../Headers/MapManager.hpp"
#include "../Headers/Hooded.hpp"
#include "../Headers/Swordsman.hpp"

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

	BackgroundManager* m_backgroundManager;
	Hooded* m_hooded;
	Swordsman* m_swordsman;
	MapManager* m_mapManager;

	WindowManager* m_windowManager;
};

