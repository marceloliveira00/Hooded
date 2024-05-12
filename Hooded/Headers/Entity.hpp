#pragma once

#include "../Headers/GameConfig.hpp"

class Entity
{
protected:
	float m_health = 10.f;
	float m_posX = 0.f;
	float m_posY = 0.f;
	float m_speed = .2f; // Default speed value for Entities

	unsigned short m_tileHeight = DEFAULT_SPRITE_SIZE_X_Y;
	unsigned short m_tileWidth = DEFAULT_SPRITE_SIZE_X_Y;
};

