#pragma once

#include <map>
#include <SFML/Graphics.hpp>

#include "../Animation.hpp"
#include "../Enums/EntityStatus.hpp"
#include "../Enums/EntityDirection.hpp"
#include "../GameConfig.hpp"

class Entity
{
public:
	const sf::FloatRect GetBounds() const { return m_sprite.getGlobalBounds(); }
	const void TakeDamage(const float damage);

protected:
	Animation* m_animation = nullptr;
	EntityDirection m_spriteDirection = EntityDirection::Right;
	EntityStatus m_spriteStatus = EntityStatus::Idle;

	float m_attackRange = 0.f;
	float m_health = 0.f;
	float m_jumpPosY = 0.f;
	float m_jumpSpeed = 0.02f;
	float m_posX = 0.f;
	float m_posY = 0.f;
	float m_speed = 0.f;
	bool m_spriteOnGround = false;
	float m_weight = 1.2f;

	unsigned short m_tileHeight = DEFAULT_SPRITE_SIZE_X_Y;
	unsigned short m_tileWidth = DEFAULT_SPRITE_SIZE_X_Y;

	sf::Sprite m_sprite;
	SpriteCoordinates m_spriteCoordinates;
	sf::RectangleShape m_spriteBoundingRectangle;
	sf::Texture m_spriteTexture;

	const virtual void DefineSpriteCoordinates(SpriteCoordinates& spriteCoordinates) const;
};

