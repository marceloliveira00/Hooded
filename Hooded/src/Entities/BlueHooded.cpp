#include "BlueHooded.hpp"

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

BlueHooded::BlueHooded()
{
	InitVariables();
	InitBlueHooded();
}

const void BlueHooded::Render(sf::RenderTarget* target) const
{
	m_animation->SetTexture(*m_spriteDirection, *m_spriteStatus);

	target->draw(m_sprite);
	target->draw(m_spriteBoundingRectangle);
}

const void BlueHooded::Update(const float deltaTime, const MapManager& mapManager)
{
	Move();
}

const void BlueHooded::Move()
{
	return void();
}
