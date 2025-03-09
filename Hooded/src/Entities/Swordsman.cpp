#include "Swordsman.hpp"

void Swordsman::InitVariables()
{
	m_health = 100.f;
	m_posX = 300.f;
	m_posY = 313.5f;
	m_speed = .08f;
}

void Swordsman::InitSwordsman()
{
	m_spriteTexture.loadFromFile("Assets/Entities/Swordsman.png");
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_tileWidth, m_tileHeight));
	m_sprite.setPosition(m_posX, m_posY);
	m_sprite.setScale(1.2f, 1.2f);
	m_sprite.setTexture(m_spriteTexture);

	m_spriteBoundingRectangle.setSize(sf::Vector2f(m_tileWidth, m_tileHeight));
	m_spriteBoundingRectangle.setFillColor(sf::Color::Transparent);
	m_spriteBoundingRectangle.setOutlineColor(sf::Color::Red);
	m_spriteBoundingRectangle.setOutlineThickness(.5f);
	m_spriteBoundingRectangle.setPosition(m_posX, m_posY);
	m_spriteBoundingRectangle.setScale(1.2f, 1.2f);
}

Swordsman::Swordsman()
{
	InitVariables();
	InitSwordsman();
}

const void Swordsman::Render(sf::RenderTarget* target) const
{
	target->draw(m_sprite);
	target->draw(m_spriteBoundingRectangle);
}

const void Swordsman::Move()
{
	return void();
}

const void Swordsman::Update(float deltaTime, MapManager& mapManager)
{
	Move();
}
