#pragma once

#include <map>

#include "Enums/EntityStatus.hpp"
#include "GameConfig.hpp"
#include "SpriteCoordinates.hpp"

class Entity
{
protected:
	float m_health = 10.f;
	float m_posX = 0.f;
	float m_posY = 0.f;
	float m_speed = .2f;

	unsigned short m_tileHeight = DEFAULT_SPRITE_SIZE_X_Y;
	unsigned short m_tileWidth = DEFAULT_SPRITE_SIZE_X_Y;

	/// Stores the row index and the number of sprites in a texture for a given status
	std::map<EntityStatus, SpriteCoordinates> m_spriteCoordinates;
};

