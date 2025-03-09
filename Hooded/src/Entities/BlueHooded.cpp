#include "BlueHooded.hpp"

void BlueHooded::InitVariables()
{
	m_health = 100.f;
	m_posX = 300.f;
	m_posY = 319.799927f;
	m_speed = .08f;
}

void BlueHooded::InitBlueHooded()
{
	m_spriteTexture.loadFromFile("Assets/Entities/Hooded_Blue.png");
	m_sprite.setTextureRect(sf::IntRect(32, 0, -m_tileWidth, m_tileHeight));
	m_sprite.setPosition(m_posX, m_posY);
	m_sprite.setTexture(m_spriteTexture);

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
	target->draw(m_sprite);
	target->draw(m_spriteBoundingRectangle);
}

const void BlueHooded::Update(float deltaTime, MapManager& mapManager)
{
	return void();
}

const void BlueHooded::Move()
{
	return void();
}
