#include "Entity.hpp"

const void Entity::TakeDamage(const float damage)
{
	m_spriteStatus = EntityStatus::TakingDamage;
	m_health -= damage;
}

const void Entity::DefineSpriteCoordinates(SpriteCoordinates& spriteCoordinates) const
{
	constexpr std::pair<unsigned short, unsigned short> attackCoordinates(8, 8);
	constexpr std::pair<unsigned short, unsigned short> crouchingCoordinates(4, 4);
	constexpr std::pair<unsigned short, unsigned short> dematerializedCoordinates(4, 6);
	constexpr std::pair<unsigned short, unsigned short> idleCoordinates(1, 0);
	constexpr std::pair<unsigned short, unsigned short> jumpingCoordinates(8, 5);
	constexpr std::pair<unsigned short, unsigned short> movingCoordinates(8, 3);
	constexpr std::pair<unsigned short, unsigned short> takingDamageCoordinates(7, 3);

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
