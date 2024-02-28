#include "../Headers/Gravity.hpp"

void Gravity()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		velocity.x = moveSpeed;
}