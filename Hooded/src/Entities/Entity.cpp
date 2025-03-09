#include "Entity.hpp"

Entity::~Entity()
{
	delete m_animation;
	delete m_spriteDirection;
	delete m_spriteStatus;
}

const void Entity::TakeDamage(const float damage)
{
	*m_spriteStatus = EntityStatus::TakingDamage;
	m_health -= damage;
}
