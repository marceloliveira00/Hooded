#include "Hooded.hpp"

void Hooded::InitVariables()
{
	health = 100.f;
	speed = .3f;
}

void Hooded::InitHooded()
{
	hoodedTexture.loadFromFile("Assets/Entities/Hooded.png");
	hooded.setPosition(600, 930);
	hooded.setScale(sf::Vector2f(3, 3));
	hooded.setTexture(hoodedTexture);
	hooded.setTextureRect(sf::IntRect(0, 0, 32, 32));
}

Hooded::Hooded()
{
	InitVariables();
	InitHooded();
}

const void Hooded::Move(float deltaTime, sf::Sprite* sprite) const
{
	sf::Vector2f position = sprite->getPosition();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		sprite->setPosition(position.x - 1 * speed * deltaTime, position.y);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		sprite->setPosition(position.x + 1 * speed * deltaTime, position.y);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		sprite->setPosition(position.x, position.y - 1 * speed * deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		sprite->setPosition(position.x, position.y + 1 * speed * deltaTime);
	}
}

const void Hooded::Render(sf::RenderTarget& target) const
{
	target.draw(hooded);
}

const void Hooded::Update(float deltaTime)
{
	Move(deltaTime, &hooded);
}
