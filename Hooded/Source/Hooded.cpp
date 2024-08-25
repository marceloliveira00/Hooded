#include "../Headers/Hooded.hpp"


const void Hooded::Actions(Camera& camera, float deltaTime, MapManager& mapManager)
{
	if (m_hoodedStatus != EntityStatus::Attacking && m_hoodedStatus != EntityStatus::Crouching && m_hoodedStatus != EntityStatus::Jumping)
	{
		m_hoodedStatus = EntityStatus::Idle;
	}

	Attack();
	ResetJump(deltaTime, mapManager);
	Move(deltaTime, mapManager);

	m_hoodedBoundingRectangle.setPosition(m_posX, m_posY);
	m_hooded.setPosition(m_posX, m_posY);
	camera.SetPosition(m_posX, m_posY);
}

static void DefineHoodedSpriteCoordinates(std::map<EntityStatus, SpriteCoordinates>& spriteCoordinates)
{
	SpriteCoordinates attackCoordinates(8, 8);
	SpriteCoordinates crouchingCoordinates(4, 4);
	SpriteCoordinates dematerializedCoordinates(4, 6);
	SpriteCoordinates idleCoordinates(1, 0);
	SpriteCoordinates jumpingCoordinates(8, 5);
	SpriteCoordinates movingCoordinates(8, 3);

	spriteCoordinates =
	{
		{ EntityStatus::Attacking, attackCoordinates },
		{ EntityStatus::Crouching, crouchingCoordinates },
		{ EntityStatus::Dematerialized, dematerializedCoordinates },
		{ EntityStatus::Idle, idleCoordinates },
		{ EntityStatus::Jumping, jumpingCoordinates },
		{ EntityStatus::Moving, movingCoordinates },
	};
}

const void Hooded::Attack()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) || m_hoodedStatus == EntityStatus::Attacking)
	{
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			m_hoodedStatus = EntityStatus::Idle;
			return;
		}

		m_hoodedStatus = EntityStatus::Attacking;
	}
}

void Hooded::InitVariables()
{
	m_health = 100.f;
	m_posX = m_initialHoodedPosX;
	m_posY = m_initialHoodedPosY;
	m_speed = .1f;

	DefineHoodedSpriteCoordinates(m_spriteCoordinates);
}

void Hooded::InitHooded()
{
	m_hoodedTexture.loadFromFile("Assets/Entities/Hooded.png");
	m_hooded.setTextureRect(sf::IntRect(0, 0, m_tileWidth, m_tileHeight));
	m_hooded.setPosition(m_posX, m_posY);
	m_hooded.setTexture(m_hoodedTexture);

	m_animation = new Animation(
		&m_hooded,
		m_spriteCoordinates,
		m_tileWidth,
		m_tileHeight
	);

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

Hooded::~Hooded()
{
	delete m_animation;
}

const void Hooded::Dematerialize()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		m_hoodedStatus = EntityStatus::Dematerialized;
	}
}

const void Hooded::Move(float deltaTime, MapManager& mapManager)
{
	if (m_hoodedStatus == EntityStatus::Attacking) return;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)
		&& !mapManager.MapCollision(m_posX, m_posY - 1 * m_speed * deltaTime,
			sf::Vector2i(m_tileWidth, m_tileHeight), m_hoodedStatus == EntityStatus::Dematerialized)
		&& m_hoodedStatus != EntityStatus::Jumping || m_jumpPosY != 0.f && m_jumpPosY < 2.f)
	{

		if (m_jumpPosY == 0) m_jumpPosY += m_gravity;

		m_jumpPosY += m_jumpSpeed;

		m_posY -= m_jumpPosY;
		m_hoodedStatus = EntityStatus::Jumping;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || m_hoodedStatus == EntityStatus::Crouching)
	{
		if (m_hoodedStatus != EntityStatus::Crouching) m_clock.restart();

		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			m_hoodedStatus = EntityStatus::Idle;
			return;
		}

		m_hoodedStatus = EntityStatus::Crouching;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !mapManager.MapCollision(m_posX - 1 * m_speed * deltaTime, m_posY,
		sf::Vector2i(m_tileWidth, m_tileHeight), m_hoodedStatus == EntityStatus::Dematerialized) && m_hoodedStatus != EntityStatus::Crouching)
	{
		m_posX -= 1 * m_speed * deltaTime;
		m_hoodedDirection = EntityDirection::Left;
		m_hoodedStatus = EntityStatus::Moving;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !mapManager.MapCollision(m_posX + 1 * m_speed * deltaTime, m_posY,
		sf::Vector2i(m_tileWidth, m_tileHeight), m_hoodedStatus == EntityStatus::Dematerialized) && m_hoodedStatus != EntityStatus::Crouching)
	{
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

	m_animation->Update(m_hoodedDirection, &m_hoodedStatus);
}
