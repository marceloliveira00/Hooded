#pragma once

#include <SFML/Graphics.hpp>

#include "Enums/EntityDirection.hpp"
#include "Enums/EntityStatus.hpp"
#include "GameConfig.hpp"

class Animation
{
public:
	Animation(
		sf::Sprite* sprite,
		const std::map<EntityStatus, std::pair<unsigned short, unsigned short>> spriteCoordinates,
		const unsigned short tileHeight,
		const unsigned short tileWidth);
	~Animation();

	const void SetTexture(const EntityDirection entityDirection, EntityStatus* entityStatus);

private:
	unsigned short m_textureIndex = 0;
	unsigned short m_tileHeight = DEFAULT_SPRITE_SIZE_X_Y;
	unsigned short m_tileWidth = DEFAULT_SPRITE_SIZE_X_Y;

	std::map<EntityStatus, std::pair<unsigned short, unsigned short>> m_spriteCoordinates;
	std::vector<EntityStatus> m_entityStatusThatLoops = { EntityStatus::Moving };

	sf::Clock m_clock;
	sf::Sprite* m_sprite;

	EntityStatus m_lastEntityStatus = EntityStatus::Idle;

	const bool CurrentEntityStateLoops(EntityStatus& entityStatus) const;
	const int GetMaxTextureIndexByMaxTileNumber(short maxTile) const;
	/// @param frames Number of frames that should wait to update the texture index
	/// @param tiles Number of tiles in the spritesheet row
	/// @param restartAnimation True if the animation should restart. False if the animation should stop on the last tile in the spritesheet row
	/// @return The texture animation index
	const int GetTextureIndex(unsigned short frames, unsigned short tiles, bool restartAnimation) const;
	const bool WaitForAnimationToEnd(const EntityStatus entityStatus) const;
};