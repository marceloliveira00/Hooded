#include "../Headers/Hooded.hpp"

void Hooded::InitVariables()
{
	m_health = 100.f;
	m_speed = .2f;
}

void Hooded::InitHooded()
{
	m_hoodedTexture.loadFromFile("Assets/Entities/Hooded.png", sf::IntRect(0, 0, tileWidth, tileHeight));
	m_hooded.setPosition(initialHoodedPosX, initialHoodedPosY);
	m_hooded.setTexture(m_hoodedTexture);

	m_hoodedBoundingRectangle.setSize(sf::Vector2f(tileWidth, tileHeight));
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

const void Hooded::Move(Camera& camera, float deltaTime, MapManager& mapManager, sf::Sprite& sprite)
{
	sf::Vector2f position = sprite.getPosition();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (!mapManager.MapCollision(sf::Vector2f(position.x - 1, position.y), sprite.getTextureRect().getSize()))
		{
			sprite.setTextureRect(sf::IntRect(tileWidth, 0, -tileWidth, tileHeight));
			sprite.setPosition(position.x - 1 * m_speed * deltaTime, position.y);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (!mapManager.MapCollision(sf::Vector2f(position.x + 1, position.y), sprite.getTextureRect().getSize()))
		{
			sprite.setTextureRect(sf::IntRect(0, 0, tileWidth, tileHeight));
			sprite.setPosition(position.x + 1 * m_speed * deltaTime, position.y);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (!mapManager.MapCollision(sf::Vector2f(position.x, position.y - 1), sprite.getTextureRect().getSize()))
		{
			sprite.setPosition(position.x, position.y - 1 * m_speed * deltaTime);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (!mapManager.MapCollision(sf::Vector2f(position.x, position.y + 1), sprite.getTextureRect().getSize()))
		{
			sprite.setPosition(position.x, position.y + 1 * m_speed * deltaTime);
		}
	}

	m_hoodedBoundingRectangle.setPosition(position.x, position.y);
	camera.SetPosition(position.x, position.y);
}

const void Hooded::Render(sf::RenderTarget* target) const
{
	target->draw(m_hooded);
	target->draw(m_hoodedBoundingRectangle);
}

const void Hooded::Update(Camera& camera, float deltaTime, MapManager& mapManager)
{
	Move(camera, deltaTime, mapManager, m_hooded);
}
