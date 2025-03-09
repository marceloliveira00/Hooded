#include "Hooded.hpp"

const void Hooded::Actions(Camera& camera, const float deltaTime, MapManager& mapManager, std::vector<Entity*>& enemies)
{
	if (*m_spriteStatus != EntityStatus::Attacking && *m_spriteStatus != EntityStatus::Crouching && m_spriteOnGround)
	{
		*m_spriteStatus = EntityStatus::Idle;
	}

	Attack(deltaTime, enemies);
	ResetJump(deltaTime, mapManager);
	Move(deltaTime, mapManager);

	m_spriteBoundingRectangle.setPosition(m_posX, m_posY);
	m_sprite.setPosition(m_posX, m_posY);
	camera.SetPosition(m_posX, m_posY);
}

#include <iostream>
void Hooded::Attack(const float deltaTime, std::vector<Entity*>& enemies)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) *m_spriteStatus = EntityStatus::Attacking;

	if (*m_spriteStatus == EntityStatus::Attacking)
	{
		sf::FloatRect attackHitbox;

		if (*m_spriteDirection == EntityDirection::Right)
			attackHitbox = sf::FloatRect(m_posX + m_tileWidth, m_posY, m_attackRange, m_tileHeight);
		else
			attackHitbox = sf::FloatRect(m_posX - m_attackRange, m_posY, m_attackRange, m_tileHeight);

		// check for collision with enemies
		for (auto& enemy : enemies)
		{
			if (enemy->GetBounds().intersects(attackHitbox))
			{
				std::cout << enemy->GetSpriteStatus() << std::endl;
				enemy->TakeDamage(10);
			}
			else std::cout << "0" << std::endl;
		}
	}
}

const void Hooded::DefineSpriteCoordinates(SpriteCoordinates& spriteCoordinates) const
{
	constexpr std::pair<unsigned short, unsigned short> attackCoordinates(8, 8);
	constexpr std::pair<unsigned short, unsigned short> crouchingCoordinates(4, 4);
	constexpr std::pair<unsigned short, unsigned short> dematerializedCoordinates(4, 6);
	constexpr std::pair<unsigned short, unsigned short> idleCoordinates(1, 0);
	constexpr std::pair<unsigned short, unsigned short> jumpingCoordinates(8, 5);
	constexpr std::pair<unsigned short, unsigned short> movingCoordinates(8, 3);
	constexpr std::pair<unsigned short, unsigned short> takingDamageCoordinates(7, 4);

	spriteCoordinates =
	{
		{ EntityStatus::Attacking, attackCoordinates },
		{ EntityStatus::Crouching, crouchingCoordinates },
		{ EntityStatus::Dematerialized, dematerializedCoordinates },
		{ EntityStatus::Idle, idleCoordinates },
		{ EntityStatus::Jumping, jumpingCoordinates },
		{ EntityStatus::Moving, movingCoordinates },
		{ EntityStatus::TakingDamage, takingDamageCoordinates },
	};
}

void Hooded::InitVariables()
{
	m_attackRange = 1.f;
	m_weight = 1.2f;
	m_health = 100.f;
	m_jumpPosY = 0.f;
	m_jumpSpeed = 0.02f;
	m_posX = 250.f;
	m_posY = 150.f;
	m_speed = .1f;

	DefineSpriteCoordinates(m_spriteCoordinates);
}

void Hooded::InitHooded()
{
	m_spriteTexture.loadFromFile("Assets/Entities/Hooded.png");
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_tileWidth, m_tileHeight));
	m_sprite.setPosition(m_posX, m_posY);
	m_sprite.setTexture(m_spriteTexture);

	m_animation = new Animation(&m_sprite, m_spriteCoordinates, m_tileWidth, m_tileHeight);

	m_spriteBoundingRectangle.setSize(sf::Vector2f(m_tileWidth, m_tileHeight));
	m_spriteBoundingRectangle.setFillColor(sf::Color::Transparent);
	m_spriteBoundingRectangle.setOutlineColor(sf::Color::Red);
	m_spriteBoundingRectangle.setOutlineThickness(.5f);
	m_spriteBoundingRectangle.setPosition(m_posX, m_posY);
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
		*m_spriteStatus = EntityStatus::Dematerialized;
}

const void Hooded::Move(const float deltaTime, MapManager& mapManager)
{
	if (*m_spriteStatus == EntityStatus::Attacking) return;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)
		&& !mapManager.MapCollision(m_posX, m_posY - 1 * m_speed * deltaTime,
			sf::Vector2i(m_tileWidth, m_tileHeight), *m_spriteStatus)
		&& *m_spriteStatus != EntityStatus::Jumping || m_jumpPosY != 0.f && m_jumpPosY < 2.f)
	{

		if (m_jumpPosY == 0) m_jumpPosY += m_weight;

		m_jumpPosY += m_jumpSpeed;

		m_posY -= m_jumpPosY;
		*m_spriteStatus = EntityStatus::Jumping;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || *m_spriteStatus == EntityStatus::Crouching)
	{
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			*m_spriteStatus = EntityStatus::Idle;
			return;
		}

		*m_spriteStatus = EntityStatus::Crouching;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !mapManager.MapCollision(m_posX - 1 * m_speed * deltaTime, m_posY,
		sf::Vector2i(m_tileWidth, m_tileHeight), *m_spriteStatus) && *m_spriteStatus != EntityStatus::Crouching)
	{
		m_posX -= 1 * m_speed * deltaTime;
		*m_spriteDirection = EntityDirection::Left;
		*m_spriteStatus = m_spriteOnGround ? EntityStatus::Moving : EntityStatus::Jumping;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !mapManager.MapCollision(m_posX + 1 * m_speed * deltaTime, m_posY,
		sf::Vector2i(m_tileWidth, m_tileHeight), *m_spriteStatus) && *m_spriteStatus != EntityStatus::Crouching)
	{
		m_posX += 1 * m_speed * deltaTime;
		*m_spriteDirection = EntityDirection::Right;
		*m_spriteStatus = m_spriteOnGround ? EntityStatus::Moving : EntityStatus::Jumping;
	}
}

const void Hooded::Render(sf::RenderTarget* target)
{
	m_animation->SetTexture(*m_spriteDirection, *m_spriteStatus);

	target->draw(m_sprite);
	target->draw(m_spriteBoundingRectangle);
}

const void Hooded::ResetJump(const float deltaTime, MapManager& mapManager)
{
	m_spriteOnGround = mapManager.SpriteOnGround(m_posX, m_posY + m_weight * m_speed * deltaTime, sf::Vector2i(m_tileWidth, m_tileHeight));
	if (m_spriteOnGround) m_jumpPosY = 0.f;
	else
	{
		m_posY += m_weight * m_speed * deltaTime;
		*m_spriteStatus = EntityStatus::Jumping;
		m_spriteOnGround = false;
	}
}

const void Hooded::Update(Camera& camera, const float deltaTime, MapManager& mapManager, std::vector<Entity*>& entities)
{
	Dematerialize();
	Actions(camera, deltaTime, mapManager, entities);
}
