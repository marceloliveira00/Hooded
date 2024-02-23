#include "../Headers/Hooded.hpp"

void Hooded::InitVariables()
{
	m_health = 100.f;
	m_speed = .3f;
}

void Hooded::InitHooded()
{
	m_hoodedTexture.loadFromFile("Assets/Entities/Hooded.png", sf::IntRect(0, 0, tileWidth, tileHeight));
	m_hooded.setPosition(initialHoodedPosX, initialHoodedPosY);
	m_hooded.setScale(sf::Vector2f(GAME_SCALE, GAME_SCALE));
	m_hooded.setTexture(m_hoodedTexture);

	m_hoodedBoundingRectangle.setSize(sf::Vector2f(tileWidth * GAME_SCALE, tileHeight * GAME_SCALE));
	m_hoodedBoundingRectangle.setFillColor(sf::Color::Transparent);
	m_hoodedBoundingRectangle.setOutlineColor(sf::Color::Red);
	m_hoodedBoundingRectangle.setOutlineThickness(1);
	m_hoodedBoundingRectangle.setPosition(initialHoodedPosX, initialHoodedPosY);
}

Hooded::Hooded()
{
	InitVariables();
	InitHooded();
}

const void Hooded::Move(float deltaTime, sf::Sprite* sprite)
{
	sf::Vector2f position = sprite->getPosition();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		sprite->setTextureRect(sf::IntRect(tileWidth, 0, -tileWidth, tileHeight));
		sprite->setPosition(position.x - 1 * m_speed * deltaTime, position.y);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		sprite->setTextureRect(sf::IntRect(0, 0, tileWidth, tileHeight));
		sprite->setPosition(position.x + 1 * m_speed * deltaTime, position.y);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		sprite->setPosition(position.x, position.y - 1 * m_speed * deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		sprite->setPosition(position.x, position.y + 1 * m_speed * deltaTime);
	}

	this->m_hoodedBoundingRectangle.setPosition(position.x, position.y);
}

const void Hooded::Render(sf::RenderTarget* target) const
{
	target->draw(m_hooded);
	target->draw(m_hoodedBoundingRectangle);
}

const void Hooded::Update(float deltaTime)
{
	Move(deltaTime, &m_hooded);
}
