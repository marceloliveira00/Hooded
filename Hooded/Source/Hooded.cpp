#include "../Headers/Hooded.hpp"


const void Hooded::Actions(Camera& camera, float deltaTime, MapManager& mapManager)
{
	m_hoodedStatus = m_hoodedStatus == EntityStatus::Attacking ? EntityStatus::Attacking : EntityStatus::Idle;

	Attack();
	ResetJump(deltaTime, mapManager);
	Move(deltaTime, mapManager);

	if (m_hoodedStatus == EntityStatus::Idle)
	{
		m_clock.restart();
		m_textureIndex = 0;
		if (m_hoodedDirection == EntityDirection::Right) m_hooded.setTextureRect(sf::IntRect(0, 0, m_tileWidth, m_tileHeight));
		else if (m_hoodedDirection == EntityDirection::Left) m_hooded.setTextureRect(sf::IntRect(32, 0, -m_tileWidth, m_tileHeight));
	}

	m_hoodedBoundingRectangle.setPosition(m_posX, m_posY);
	m_hooded.setPosition(m_posX, m_posY);
	camera.SetPosition(m_posX, m_posY);
}

const void Hooded::Attack()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) || m_hoodedStatus == EntityStatus::Attacking)
	{
		m_hoodedStatus = EntityStatus::Attacking;
		const unsigned short tiles = 8;

		if (m_textureIndex == GetMaxTextureIndexByMaxTileNumber(tiles))
		{
			m_hoodedStatus = EntityStatus::Idle;
			return;
		}

		m_textureIndex = GetTextureIndex(100, tiles, false);

		if (m_hoodedDirection == EntityDirection::Right)
			m_hooded.setTextureRect(sf::IntRect(m_textureIndex, m_tileHeight * 8, m_tileWidth, m_tileHeight));
		else if (m_hoodedDirection == EntityDirection::Left)
			m_hooded.setTextureRect(sf::IntRect(m_textureIndex + 32, m_tileHeight * 8, -m_tileWidth, m_tileHeight));
	}
}

void Hooded::InitVariables()
{
	m_health = 100.f;
	m_posX = m_initialHoodedPosX;
	m_posY = m_initialHoodedPosY;
	m_speed = .1f;
}

void Hooded::InitHooded()
{
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

Hooded::Hooded()
{
	InitVariables();
	InitHooded();
}

const void Hooded::Dematerialize()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (m_hoodedStatus != EntityStatus::Jumping) m_textureIndex = GetTextureIndex(100, 4, false);

		if (m_hoodedDirection == EntityDirection::Right)
			m_hooded.setTextureRect(sf::IntRect(m_textureIndex, m_tileHeight * 6, m_tileWidth, m_tileHeight));
		else if (m_hoodedDirection == EntityDirection::Left)
			m_hooded.setTextureRect(sf::IntRect(m_textureIndex + 32, m_tileHeight * 6, -m_tileWidth, m_tileHeight));

		m_hoodedStatus = EntityStatus::Dematerialized;
	}
}

const int Hooded::GetMaxTextureIndexByMaxTileNumber(short maxTile) const { return (maxTile - 1) * m_tileWidth; }

const int Hooded::GetTextureIndex(unsigned short frames, unsigned short tiles, bool restartAnimation) const
{
	if (!restartAnimation && m_textureIndex == (tiles - 1) * m_tileWidth) return m_textureIndex;

	return (m_clock.getElapsedTime().asMilliseconds() / frames % tiles) * m_tileWidth;
}

const void Hooded::Move(float deltaTime, MapManager& mapManager)
{
	if (m_hoodedStatus == EntityStatus::Attacking) return;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)
		&& !mapManager.MapCollision(m_posX, m_posY - 1 * m_speed * deltaTime,
			sf::Vector2i(m_tileWidth, m_tileHeight), m_hoodedStatus == EntityStatus::Dematerialized)
		&& m_hoodedStatus != EntityStatus::Jumping || m_jumpPosY != 0.f && m_jumpPosY < 2.f)
	{
		m_textureIndex = 0;

		if (m_jumpPosY == 0) m_jumpPosY += m_gravity;

		m_jumpPosY += m_jumpSpeed;

		m_posY -= m_jumpPosY;
		m_hoodedStatus = EntityStatus::Jumping;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (m_hoodedStatus != EntityStatus::Jumping) m_textureIndex = GetTextureIndex(100, 4, false);

		if (m_hoodedDirection == EntityDirection::Right)
			m_hooded.setTextureRect(sf::IntRect(m_textureIndex, m_tileHeight * 4, m_tileWidth, m_tileHeight));
		else if (m_hoodedDirection == EntityDirection::Left)
			m_hooded.setTextureRect(sf::IntRect(m_textureIndex + 32, m_tileHeight * 4, -m_tileWidth, m_tileHeight));

		m_hoodedStatus = EntityStatus::Crouching;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !mapManager.MapCollision(m_posX - 1 * m_speed * deltaTime, m_posY,
		sf::Vector2i(m_tileWidth, m_tileHeight), m_hoodedStatus == EntityStatus::Dematerialized) && m_hoodedStatus != EntityStatus::Crouching)
	{
		m_textureIndex = 0;
		if (m_hoodedStatus != EntityStatus::Jumping) m_textureIndex = GetTextureIndex(100, 8, true);

		m_hooded.setTextureRect(sf::IntRect(m_textureIndex + 32, m_tileHeight * 3, -m_tileWidth, m_tileHeight));
		m_posX -= 1 * m_speed * deltaTime;
		m_hoodedDirection = EntityDirection::Left;
		m_hoodedStatus = EntityStatus::Moving;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !mapManager.MapCollision(m_posX + 1 * m_speed * deltaTime, m_posY,
		sf::Vector2i(m_tileWidth, m_tileHeight), m_hoodedStatus == EntityStatus::Dematerialized) && m_hoodedStatus != EntityStatus::Crouching)
	{
		m_textureIndex = 0;
		if (m_hoodedStatus != EntityStatus::Jumping) m_textureIndex = GetTextureIndex(100, 8, true);

		m_hooded.setTextureRect(sf::IntRect(m_textureIndex, m_tileHeight * 3, m_tileWidth, m_tileHeight));
		m_posX += 1 * m_speed * deltaTime;
		m_hoodedDirection = EntityDirection::Right;
		m_hoodedStatus = EntityStatus::Moving;
	}
}

const void Hooded::Render(sf::RenderTarget* target) const
{
	target->draw(m_hooded);
	target->draw(m_hoodedBoundingRectangle);
}

const void Hooded::ResetJump(float deltaTime, MapManager& mapManager)
{
	if (mapManager.SpriteOnGround(m_posX, m_posY + m_gravity * m_speed * deltaTime, sf::Vector2i(m_tileWidth, m_tileHeight)))
	{
		m_jumpPosY = 0.f;
	}
	else
	{
		m_posY += m_gravity * m_speed * deltaTime;
		m_hoodedStatus = EntityStatus::Jumping;
	}
}

const void Hooded::Update(Camera& camera, float deltaTime, MapManager& mapManager)
{
	Dematerialize();
	Actions(camera, deltaTime, mapManager);
}