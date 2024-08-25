#include "../Headers/Animation.hpp"

Animation::Animation(
	sf::Sprite* sprite,
	std::map<EntityStatus, SpriteCoordinates> spriteCoordinates,
	unsigned short tileHeight,
	unsigned short tileWidth)
{
	m_sprite = sprite;
	m_spriteCoordinates = spriteCoordinates;
	m_tileHeight = tileHeight;
	m_tileWidth = tileWidth;
}

Animation::~Animation() { }

const bool Animation::CurrentEntityStateLoops(EntityStatus& entityStatus) const
{
	return std::count(m_entityStatusThatLoops.begin(), m_entityStatusThatLoops.end(), entityStatus) > 0;
}

const int Animation::GetMaxTextureIndexByMaxTileNumber(short maxTile) const { return (maxTile - 1) * m_tileWidth; }

const int Animation::GetTextureIndex(unsigned short frames, unsigned short tiles, bool restartAnimation) const
{
	if (!restartAnimation && m_textureIndex == (tiles - 1) * m_tileWidth) return m_textureIndex;

	return (m_clock.getElapsedTime().asMilliseconds() / frames % tiles) * m_tileWidth;
}

const void Animation::Update(const EntityDirection currentEntityDirection, EntityStatus* currentEntityStatus)
{
	short rectLeft = 0;
	short rectWidth = m_tileWidth;

	if (*currentEntityStatus != m_lastEntityStatus) m_clock.restart();

	// if the tile width is negative, the image turns backwards
	if (currentEntityDirection == EntityDirection::Left)
	{
		rectLeft = m_tileWidth;
		rectWidth = -rectWidth;
	}

	SpriteCoordinates spriteCoordinates = m_spriteCoordinates[*currentEntityStatus];
	m_lastEntityStatus = *currentEntityStatus;
	m_textureIndex = GetTextureIndex(100, spriteCoordinates.colNumber, CurrentEntityStateLoops(*currentEntityStatus));

	switch (*currentEntityStatus)
	{
	case EntityStatus::Attacking:
		m_sprite->setTextureRect(sf::IntRect(m_textureIndex + rectLeft, m_tileHeight * spriteCoordinates.rowIndex, rectWidth, m_tileHeight));
	case EntityStatus::Crouching:
		m_sprite->setTextureRect(sf::IntRect(m_textureIndex + rectLeft, m_tileHeight * spriteCoordinates.rowIndex, rectWidth, m_tileHeight));
	case EntityStatus::Dematerialized:
		m_sprite->setTextureRect(sf::IntRect(m_textureIndex + rectLeft, m_tileHeight * spriteCoordinates.rowIndex, rectWidth, m_tileHeight));
	case EntityStatus::Idle:
		m_sprite->setTextureRect(sf::IntRect(m_textureIndex + rectLeft, m_tileHeight * spriteCoordinates.rowIndex, rectWidth, m_tileHeight));
	case EntityStatus::Jumping:
		if (m_textureIndex == GetMaxTextureIndexByMaxTileNumber(spriteCoordinates.colNumber))
			break;
		m_sprite->setTextureRect(sf::IntRect(m_textureIndex + rectLeft, m_tileHeight * spriteCoordinates.rowIndex, rectWidth, m_tileHeight));
	case EntityStatus::Moving:
		m_sprite->setTextureRect(sf::IntRect(m_textureIndex + rectLeft, m_tileHeight * spriteCoordinates.rowIndex, rectWidth, m_tileHeight));
	default:
		return;
	}
}
