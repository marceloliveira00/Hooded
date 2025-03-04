#include "../Headers/Swordsman.hpp"

void Swordsman::InitVariables()
{
	m_health = 100.f;
	m_posX = m_initialSwordsmanPosX;
	m_posY = m_initialSwordsmanPosY;
	m_speed = .08f;
}

void Swordsman::InitSwordsman()
{
	m_swordsmanTexture.loadFromFile("Assets/Entities/Swordsman.png");
	m_swordsman.setTextureRect(sf::IntRect(0, 0, m_tileWidth, m_tileHeight));
	m_swordsman.setPosition(m_posX, m_posY);
	m_swordsman.setScale(1.2f, 1.2f);
	m_swordsman.setTexture(m_swordsmanTexture);

	m_swordsmanBoundingRectangle.setSize(sf::Vector2f(m_tileWidth, m_tileHeight));
	m_swordsmanBoundingRectangle.setFillColor(sf::Color::Transparent);
	m_swordsmanBoundingRectangle.setOutlineColor(sf::Color::Red);
	m_swordsmanBoundingRectangle.setOutlineThickness(1);
	m_swordsmanBoundingRectangle.setPosition(m_posX, m_posY);
	m_swordsmanBoundingRectangle.setScale(1.2f, 1.2f);
}

Swordsman::Swordsman()
{
	InitVariables();
	InitSwordsman();
}

const void Swordsman::Render(sf::RenderTarget* target) const
{
	target->draw(m_swordsman);
	target->draw(m_swordsmanBoundingRectangle);
}

const void Swordsman::Move()
{
	return void();
}

const void Swordsman::Update(float deltaTime, MapManager& mapManager)
{
	Move();
}
