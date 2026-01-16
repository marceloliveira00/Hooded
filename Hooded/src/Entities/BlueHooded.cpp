#include "BlueHooded.hpp"

const void BlueHooded::Actions(const float deltaTime, const MapManager& mapManager)
{
	Jump(deltaTime, mapManager);

	if (*m_spriteStatus != EntityStatus::Attacking && *m_spriteStatus != EntityStatus::Crouching
		&& *m_spriteStatus != EntityStatus::TakingDamage && m_spriteOnGround)
	{
		Move(deltaTime, mapManager);
	}
}

BlueHooded::BlueHooded()
{
	InitVariables();
	InitBlueHooded();
}

const void BlueHooded::DefineSpriteCoordinates(SpriteCoordinates& spriteCoordinates) const
{
	constexpr std::pair<unsigned short, unsigned short> attackCoordinates(8, 8);
	constexpr std::pair<unsigned short, unsigned short> crouchingCoordinates(4, 4);
	constexpr std::pair<unsigned short, unsigned short> dematerializedCoordinates(4, 6);
	constexpr std::pair<unsigned short, unsigned short> idleCoordinates(1, 0);
	constexpr std::pair<unsigned short, unsigned short> jumpingCoordinates(8, 5);
	constexpr std::pair<unsigned short, unsigned short> movingCoordinates(8, 3);
	constexpr std::pair<unsigned short, unsigned short> takingDamageCoordinates(5, 7);

	spriteCoordinates =
	{
		{ EntityStatus::Attacking, attackCoordinates },
		{ EntityStatus::Crouching, crouchingCoordinates },
		{ EntityStatus::Dematerialized, dematerializedCoordinates },
		{ EntityStatus::Idle, idleCoordinates },
		{ EntityStatus::Jumping, jumpingCoordinates },
		{ EntityStatus::Moving, movingCoordinates },
		{ EntityStatus::TakingDamage, takingDamageCoordinates },
	};
}

const void BlueHooded::InitVariables()
{
	m_attackRange = 1.f;
	m_weight = 1.2f;
	m_health = 100.f;
	m_jumpPosY = 0.f;
	m_jumpSpeed = 0.02f;
	m_health = 100.f;
	m_posX = 300.f;
	m_posY = 319.799927f;
	m_speed = .08f;

	DefineSpriteCoordinates(m_spriteCoordinates);
}

const void BlueHooded::InitBlueHooded()
{
	m_spriteTexture.loadFromFile("Assets/Entities/Hooded_Blue.png");
	m_sprite.setTextureRect(sf::IntRect(32, 0, -m_tileWidth, m_tileHeight));
	m_sprite.setPosition(m_posX, m_posY);
	m_sprite.setTexture(m_spriteTexture);
	*m_spriteDirection = EntityDirection::Left;

	m_animation = new Animation(&m_sprite, m_spriteCoordinates, m_tileWidth, m_tileHeight);

	m_spriteBoundingRectangle.setSize(sf::Vector2f(m_tileWidth, m_tileHeight));
	m_spriteBoundingRectangle.setFillColor(sf::Color::Transparent);
	m_spriteBoundingRectangle.setOutlineColor(sf::Color::Blue);
	m_spriteBoundingRectangle.setOutlineThickness(.5);
	m_spriteBoundingRectangle.setPosition(m_posX, m_posY);
}

const void BlueHooded::Jump(const float deltaTime, const MapManager& mapManager)
{
	m_spriteOnGround = mapManager.SpriteOnGround(m_posX, m_posY + m_weight * m_speed * deltaTime, sf::Vector2i(m_tileWidth, m_tileHeight));
	if (m_spriteOnGround) m_jumpPosY = 0.f;
	else
	{
		m_posY += m_weight * m_speed * deltaTime;
		*m_spriteStatus = EntityStatus::Jumping;
		m_spriteOnGround = false;
	}
}

const void BlueHooded::Render(sf::RenderTarget* target) const
{
	m_animation->SetTexture(*m_spriteDirection, *m_spriteStatus);

	target->draw(m_sprite);
	target->draw(m_spriteBoundingRectangle);
}

const void BlueHooded::Update(const float deltaTime, const MapManager& mapManager)
{
	Actions(deltaTime, mapManager);

	m_spriteBoundingRectangle.setPosition(m_posX, m_posY);
	m_sprite.setPosition(m_posX, m_posY);
}

const void BlueHooded::Move(const float deltaTime, const MapManager& mapManager)
{
	bool movingRight = *m_spriteDirection == EntityDirection::Right;
	float moveAmount = m_speed * deltaTime;
	float nextPosX = m_posX + (movingRight ? moveAmount : -moveAmount);

	if (!mapManager.MapCollision(nextPosX, m_posY, sf::Vector2i(m_tileWidth, m_tileHeight), *m_spriteStatus)
		&& mapManager.SpriteOnGround(nextPosX + (movingRight ? m_tileWidth : 0), m_posY + m_weight * m_speed * deltaTime, sf::Vector2i(m_tileWidth, m_tileHeight)))
	{
		m_posX = nextPosX;
		*m_spriteDirection = movingRight ? EntityDirection::Right : EntityDirection::Left;
		*m_spriteStatus = EntityStatus::Moving;
	}
	else *m_spriteDirection = movingRight ? EntityDirection::Left : EntityDirection::Right;
}
