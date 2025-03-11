#include "Skeleton.hpp"

const void Skeleton::InitVariables()
{
	m_health = 100.f;
	m_posX = 300.f;
	m_posY = 319.799927f;
	m_speed = .08f;
	m_tileWidth = 34;
	m_tileHeight = 32;
}

const void Skeleton::InitSkeleton()
{
	m_spriteTexture.loadFromFile("Assets/Entities/Skeleton.png");
	m_sprite.setTextureRect(sf::IntRect(8, 16, m_tileWidth, m_tileHeight));
	m_sprite.setPosition(m_posX, m_posY);
	m_sprite.setTexture(m_spriteTexture);

	m_spriteBoundingRectangle.setSize(sf::Vector2f(m_tileWidth, m_tileHeight));
	m_spriteBoundingRectangle.setFillColor(sf::Color::Transparent);
	m_spriteBoundingRectangle.setOutlineColor(sf::Color::Red);
	m_spriteBoundingRectangle.setOutlineThickness(.5f);
	m_spriteBoundingRectangle.setPosition(m_posX, m_posY);
}

Skeleton::Skeleton()
{
	InitVariables();
	InitSkeleton();
}

const void Skeleton::Render(sf::RenderTarget* target) const
{
	target->draw(m_sprite);
	target->draw(m_spriteBoundingRectangle);
}

const void Skeleton::Update(const float deltaTime, MapManager& mapManager)
{
	Move();
}

const void Skeleton::Move()
{
	return void();
}
