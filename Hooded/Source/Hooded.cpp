#include "../Headers/Hooded.hpp"

void Hooded::InitVariables()
{
	m_health = 100.f;
	m_speed = .2f;
}

void Hooded::InitHooded()
{
	m_hoodedTexture.loadFromFile("Assets/Entities/Hooded.png", sf::IntRect(0, 0, m_tileWidth, m_tileHeight));
	m_hooded.setPosition(m_initialHoodedPosX, m_initialHoodedPosY);
	m_hooded.setTexture(m_hoodedTexture);

	m_hoodedBoundingRectangle.setSize(sf::Vector2f(m_tileWidth, m_tileHeight));
	m_hoodedBoundingRectangle.setFillColor(sf::Color::Transparent);
	m_hoodedBoundingRectangle.setOutlineColor(sf::Color::Red);
	m_hoodedBoundingRectangle.setOutlineThickness(1);
	m_hoodedBoundingRectangle.setPosition(m_initialHoodedPosX, m_initialHoodedPosY);
}

Hooded::Hooded()
{
	InitVariables();
	InitHooded();
}

const void Hooded::Move(Camera& camera, float deltaTime, MapManager& mapManager, sf::Sprite& sprite)
{
	sf::Vector2f position = sprite.getPosition();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) m_dematerialized = !m_dematerialized;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !mapManager.MapCollision(m_dematerialized,
		sf::Vector2f(position.x - 1 * m_speed * deltaTime, position.y), sprite.getTextureRect().getSize()))
	{
		// comment below flips the sprite but also generates a bug with collision
		//sprite.setTextureRect(sf::IntRect(m_tileWidth, 0, -m_tileWidth, m_tileHeight));
		sprite.setPosition(position.x - 1 * m_speed * deltaTime, position.y);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !mapManager.MapCollision(m_dematerialized,
		sf::Vector2f(position.x + 1 * m_speed * deltaTime, position.y), sprite.getTextureRect().getSize()))
	{
		sprite.setTextureRect(sf::IntRect(0, 0, m_tileWidth, m_tileHeight));
		sprite.setPosition(position.x + 1 * m_speed * deltaTime, position.y);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !mapManager.MapCollision(m_dematerialized,
		sf::Vector2f(position.x, position.y - 1 * m_speed * deltaTime), sprite.getTextureRect().getSize()))
	{
		sprite.setPosition(position.x, position.y - 1 * m_speed * deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !mapManager.MapCollision(m_dematerialized,
		sf::Vector2f(position.x, position.y + 1 * m_speed * deltaTime), sprite.getTextureRect().getSize()))
	{
		sprite.setPosition(position.x, position.y + 1 * m_speed * deltaTime);
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
