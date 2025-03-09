#pragma once

#include <vector>

#include "BackgroundManager.hpp"
#include "MapManager.hpp"
#include "WindowManager.hpp"
#include "../Entities/Hooded.hpp"
#include "../Entities/BlueHooded.hpp"

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
	BlueHooded* m_blueHooded;
	MapManager* m_mapManager;

	WindowManager* m_windowManager;
};

