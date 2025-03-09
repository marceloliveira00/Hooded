#include "Animation.hpp"

Animation::Animation(
	sf::Sprite* sprite,
	const std::map<EntityStatus, SpriteCoordinates> spriteCoordinates,
	const unsigned short tileHeight,
	const unsigned short tileWidth)
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

const void Animation::SetTexture(const EntityDirection entityDirection, EntityStatus* entityStatus)
{
	short rectLeft = 0;
	short rectWidth = m_tileWidth;

	// if the tile width is negative, the image turns backwards
	if (entityDirection == EntityDirection::Left)
	{
		rectLeft = m_tileWidth;
		rectWidth = -rectWidth;
	}

	SpriteCoordinates coordinates = m_spriteCoordinates[*entityStatus];

	if (WaitForAnimationToEnd(*entityStatus) && m_textureIndex == GetMaxTextureIndexByMaxTileNumber(coordinates.colNumber))
	{
		*entityStatus = EntityStatus::Idle;
		return;
	}

	if (*entityStatus != m_lastEntityStatus) m_clock.restart();

	m_lastEntityStatus = *entityStatus;
	m_textureIndex = GetTextureIndex(100, coordinates.colNumber, CurrentEntityStateLoops(*entityStatus));

	switch (*entityStatus)
	{
	case EntityStatus::Attacking:
		m_sprite->setTextureRect(sf::IntRect(m_textureIndex + rectLeft, m_tileHeight * coordinates.rowIndex, rectWidth, m_tileHeight));
	case EntityStatus::Crouching:
		m_sprite->setTextureRect(sf::IntRect(m_textureIndex + rectLeft, m_tileHeight * coordinates.rowIndex, rectWidth, m_tileHeight));
	case EntityStatus::Dematerialized:
		m_sprite->setTextureRect(sf::IntRect(m_textureIndex + rectLeft, m_tileHeight * coordinates.rowIndex, rectWidth, m_tileHeight));
	case EntityStatus::Idle:
		m_sprite->setTextureRect(sf::IntRect(m_textureIndex + rectLeft, m_tileHeight * coordinates.rowIndex, rectWidth, m_tileHeight));
	case EntityStatus::Jumping:
		m_sprite->setTextureRect(sf::IntRect(m_textureIndex + rectLeft, m_tileHeight * coordinates.rowIndex, rectWidth, m_tileHeight));
	case EntityStatus::Moving:
		m_sprite->setTextureRect(sf::IntRect(m_textureIndex + rectLeft, m_tileHeight * coordinates.rowIndex, rectWidth, m_tileHeight));
	default:
		return;
	}
}

const bool Animation::WaitForAnimationToEnd(const EntityStatus entityStatus) const
{
	switch (entityStatus)
	{
	case EntityStatus::Attacking:
		return true;
	case EntityStatus::Crouching:
		return false;
	case EntityStatus::Dematerialized:
		return false;
	case EntityStatus::Idle:
		return false;
	case EntityStatus::Jumping:
		return false;
	case EntityStatus::Moving:
		return false;
	default:
		break;
	}

	return false;
}
