#include "../Headers/BlueHooded.hpp"

void BlueHooded::InitVariables()
{
	m_health = 100.f;
	m_posX = m_initialBlueHoodedPosX;
	m_posY = m_initialBlueHoodedPosY;
	m_speed = .08f;
}

void BlueHooded::InitBlueHooded()
{
	m_blueHoodedTexture.loadFromFile("Assets/Entities/Hooded_Blue.png");
	m_blueHooded.setTextureRect(sf::IntRect(32, 0, -m_tileWidth, m_tileHeight));
	m_blueHooded.setPosition(m_posX, m_posY);
	m_blueHooded.setTexture(m_blueHoodedTexture);

	m_blueHoodedBoundingRectangle.setSize(sf::Vector2f(m_tileWidth, m_tileHeight));
	m_blueHoodedBoundingRectangle.setFillColor(sf::Color::Transparent);
	m_blueHoodedBoundingRectangle.setOutlineColor(sf::Color::Red);
	m_blueHoodedBoundingRectangle.setOutlineThickness(1);
	m_blueHoodedBoundingRectangle.setPosition(m_posX, m_posY);
}

BlueHooded::BlueHooded()
{
	InitVariables();
	InitBlueHooded();
}

const void BlueHooded::Render(sf::RenderTarget* target) const
{
	target->draw(m_blueHooded);
	target->draw(m_blueHoodedBoundingRectangle);
}

const void BlueHooded::Update(float deltaTime, MapManager& mapManager)
{
	return void();
}

const void BlueHooded::Move()
{
	return void();
}
