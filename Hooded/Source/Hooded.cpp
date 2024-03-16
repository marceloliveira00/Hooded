#include "../Headers/Hooded.hpp"

#include <iostream>

void Hooded::InitVariables()
{
	m_health = 100.f;
	m_speed = .1f;
}

void Hooded::InitHooded()
{
	m_posX = m_initialHoodedPosX;
	m_posY = m_initialHoodedPosY;

	m_hoodedTexture.loadFromFile("Assets/Entities/Hooded.png");
	m_hooded.setTextureRect(sf::IntRect(0, 0, m_tileWidth, m_tileHeight));
	m_hooded.setPosition(m_posX, m_posY);
	m_hooded.setTexture(m_hoodedTexture);

	m_hoodedBoundingRectangle.setSize(sf::Vector2f(m_tileWidth, m_tileHeight));
	m_hoodedBoundingRectangle.setFillColor(sf::Color::Transparent);
	m_hoodedBoundingRectangle.setOutlineColor(sf::Color::Red);
	m_hoodedBoundingRectangle.setOutlineThickness(1);
	m_hoodedBoundingRectangle.setPosition(m_posX, m_posY);
}

const void Hooded::Dematerialize()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) m_dematerialized = !m_dematerialized;
}

Hooded::Hooded()
{
	InitVariables();
	InitHooded();
}

const void Hooded::Move(Camera& camera, float deltaTime, MapManager& mapManager)
{
	// Gravity
	if (mapManager.SpriteOnGround(m_posX, m_posY + m_gravity * m_speed * deltaTime, sf::Vector2i(m_tileWidth, m_tileHeight)))
	{
		m_onGround = true;
		m_jumpPosY = 0.f;
	}
	else
	{
		m_posY += m_gravity * m_speed * deltaTime;
		m_onGround = false;
	}

	int textureIndex = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !mapManager.MapCollision(m_posX - 1 * m_speed * deltaTime, m_posY,
		sf::Vector2i(m_tileWidth, m_tileHeight), m_dematerialized))
	{
		textureIndex = 0;
		textureIndex = (int)m_posX / 10 % 8;
		textureIndex *= m_tileWidth;

		m_hooded.setTextureRect(sf::IntRect(textureIndex + 32, m_tileHeight * 3, -m_tileWidth, m_tileHeight));
		std::cout << "textureIndex: " << textureIndex << std::endl;
		m_posX -= 1 * m_speed * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !mapManager.MapCollision(m_posX + 1 * m_speed * deltaTime, m_posY,
		sf::Vector2i(m_tileWidth, m_tileHeight), m_dematerialized))
	{
		textureIndex = 0;
		textureIndex = (int)m_posX / 10 % 8;
		textureIndex *= m_tileWidth;

		m_hooded.setTextureRect(sf::IntRect(textureIndex, m_tileHeight * 3, m_tileWidth, m_tileHeight));
		std::cout << "textureIndex: " << textureIndex << std::endl;
		m_posX += 1 * m_speed * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !mapManager.MapCollision(m_posX, m_posY - 1 * m_speed * deltaTime,
		sf::Vector2i(m_tileWidth, m_tileHeight), m_dematerialized) && m_onGround || m_jumpPosY != 0.f && m_jumpPosY < 5.f)
	{
		if (m_jumpPosY == 0) m_jumpPosY += m_gravity;

		m_jumpPosY += m_jumpSpeed;

		m_posY -= m_jumpPosY;
		m_onGround = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !mapManager.MapCollision(m_posX, m_posY + 1 * m_speed * deltaTime,
		sf::Vector2i(m_tileWidth, m_tileHeight), m_dematerialized))
	{
		m_hooded.setTextureRect(sf::IntRect(0, 0, m_tileWidth, m_tileHeight));
		m_posY += 1 * m_speed * deltaTime;
	}

	m_hoodedBoundingRectangle.setPosition(m_posX, m_posY);
	m_hooded.setPosition(m_posX, m_posY);
	camera.SetPosition(m_posX, m_posY);
}

const void Hooded::Render(sf::RenderTarget* target) const
{
	target->draw(m_hooded);
	target->draw(m_hoodedBoundingRectangle);
}

const void Hooded::Update(Camera& camera, float deltaTime, MapManager& mapManager)
{
	Dematerialize();
	Move(camera, deltaTime, mapManager);
}
