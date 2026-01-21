#include "Hooded.hpp"

const void Hooded::Actions(const float deltaTime, const MapManager& mapManager, const std::vector<Entity*>& enemies)
{
	if (*m_spriteStatus != EntityStatus::Attacking && *m_spriteStatus != EntityStatus::Crouching && m_spriteOnGround)
		*m_spriteStatus = EntityStatus::Idle;

	Attack(deltaTime, enemies);
	Move(deltaTime, mapManager);
}

const void Hooded::Attack(const float deltaTime, const std::vector<Entity*>& enemies)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) *m_spriteStatus = EntityStatus::Attacking;

	if (*m_spriteStatus == EntityStatus::Attacking)
	{
		sf::FloatRect attackHitbox;

		if (*m_spriteDirection == EntityDirection::Right)
			attackHitbox = sf::FloatRect(m_posX + m_tileWidth, m_posY, m_attackRange, m_tileHeight);
		else
			attackHitbox = sf::FloatRect(m_posX - m_attackRange, m_posY, m_attackRange, m_tileHeight);

		for (auto& enemy : enemies)
			if (enemy->GetBounds().intersects(attackHitbox)) enemy->TakeDamage(10); // check for collision with enemies
	}
}

const void Hooded::DefineSpriteCoordinates(SpriteCoordinates& spriteCoordinates) const
{
	constexpr std::pair<unsigned short, unsigned short> attackCoordinates(8, 8);
	constexpr std::pair<unsigned short, unsigned short> crouchingCoordinates(4, 4);
	constexpr std::pair<unsigned short, unsigned short> dematerializedCoordinates(4, 6);
	constexpr std::pair<unsigned short, unsigned short> idleCoordinates(1, 0);
	constexpr std::pair<unsigned short, unsigned short> jumpingCoordinates(3, 5);
	constexpr std::pair<unsigned short, unsigned short> movingCoordinates(8, 3);
	constexpr std::pair<unsigned short, unsigned short> takingDamageCoordinates(7, 4);

	spriteCoordinates = {
		{ EntityStatus::Attacking, attackCoordinates },
		{ EntityStatus::Crouching, crouchingCoordinates },
		{ EntityStatus::Dematerialized, dematerializedCoordinates },
		{ EntityStatus::Idle, idleCoordinates },
		{ EntityStatus::Jumping, jumpingCoordinates },
		{ EntityStatus::Moving, movingCoordinates },
		{ EntityStatus::TakingDamage, takingDamageCoordinates },
	};
}

const void Hooded::Dematerialize() const
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		*m_spriteStatus = EntityStatus::Dematerialized;
}

Hooded::Hooded()
{
	InitVariables();
	InitHooded();
}

const void Hooded::InitHooded()
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

const void Hooded::InitVariables()
{
	m_attackRange = 1.f;
	m_weight = 2.f;
	m_health = 100.f;
	m_jumpPosY = 0.f;
	m_jumpForce = .003f;
	m_maxJumpPosY = 0.6f;
	m_posX = 250.f;
	m_posY = 150.f;
	m_speed = 0.1f;

	DefineSpriteCoordinates(m_spriteCoordinates);
}

const void Hooded::ResetJump(const float deltaTime, const MapManager& mapManager)
{
	m_jumpKeyReleased = true;

	if (m_spriteOnGround) m_jumpPosY = 0.f;
	else m_posY += m_weight * GRAVITY * deltaTime;
}

const void Hooded::Move(const float deltaTime, const MapManager& mapManager)
{
	m_spriteOnGround = mapManager.SpriteOnGround(m_posX, m_posY + m_weight * GRAVITY * deltaTime, sf::Vector2i(m_tileWidth, m_tileHeight));

	if (*m_spriteStatus == EntityStatus::Attacking) return;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && (m_spriteOnGround || !m_jumpKeyReleased))
	{
		if (!mapManager.MapCollision(m_posX, m_posY - m_weight * GRAVITY * deltaTime, sf::Vector2i(m_tileWidth, m_tileHeight), *m_spriteStatus)
			&& m_jumpPosY < m_maxJumpPosY)
		{
			m_jumpKeyReleased = false;
			m_jumpPosY += m_jumpForce * deltaTime;
			m_posY -= m_jumpPosY * deltaTime;
			*m_spriteStatus = EntityStatus::Jumping;
		}
	}
	else ResetJump(deltaTime, mapManager);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) *m_spriteStatus = EntityStatus::Crouching;
	else if (*m_spriteStatus == EntityStatus::Crouching) *m_spriteStatus = EntityStatus::Idle;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)
		&& !mapManager.MapCollision(m_posX - m_speed * deltaTime, m_posY, sf::Vector2i(m_tileWidth, m_tileHeight), *m_spriteStatus)
		&& *m_spriteStatus != EntityStatus::Crouching)
	{
		m_posX -= m_speed * deltaTime;
		*m_spriteDirection = EntityDirection::Left;
		*m_spriteStatus = m_spriteOnGround ? EntityStatus::Moving : EntityStatus::Jumping;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)
		&& !mapManager.MapCollision(m_posX + m_speed * deltaTime, m_posY, sf::Vector2i(m_tileWidth, m_tileHeight), *m_spriteStatus)
		&& *m_spriteStatus != EntityStatus::Crouching)
	{
		m_posX += m_speed * deltaTime;
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

const void Hooded::Update(Camera& camera, const float deltaTime, const MapManager& mapManager, const std::vector<Entity*>& entities)
{
	Dematerialize();
	Actions(deltaTime, mapManager, entities);

	m_spriteBoundingRectangle.setPosition(m_posX, m_posY);
	m_sprite.setPosition(m_posX, m_posY);
	camera.SetPosition(m_posX, m_posY);
}
