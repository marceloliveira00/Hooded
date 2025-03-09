#include "Entity.hpp"

const void Entity::TakeDamage(const float damage)
{
	m_health -= damage;
}

void Entity::DefineSpriteCoordinates(std::map<EntityStatus, SpriteCoordinates>& spriteCoordinates)
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
