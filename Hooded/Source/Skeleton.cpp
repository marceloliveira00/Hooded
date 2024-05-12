#include "../Headers/Skeleton.hpp"

void Skeleton::InitVariables()
{
	m_health = 100.f;
	m_posX = m_initialSkeletonPosX;
	m_posY = m_initialSkeletonPosY;
	m_speed = .08f;
	m_tileWidth = 34;
	m_tileHeight = 32;
}

void Skeleton::InitSkeleton()
{
	m_skeletonTexture.loadFromFile("Assets/Entities/Skeleton.png");
	m_skeleton.setTextureRect(sf::IntRect(8, 16, m_tileWidth, m_tileHeight));
	m_skeleton.setPosition(m_posX, m_posY);
	m_skeleton.setTexture(m_skeletonTexture);

	m_skeletonBoundingRectangle.setSize(sf::Vector2f(m_tileWidth, m_tileHeight));
	m_skeletonBoundingRectangle.setFillColor(sf::Color::Transparent);
	m_skeletonBoundingRectangle.setOutlineColor(sf::Color::Red);
	m_skeletonBoundingRectangle.setOutlineThickness(1);
	m_skeletonBoundingRectangle.setPosition(m_posX, m_posY);
}

Skeleton::Skeleton()
{
	InitVariables();
	InitSkeleton();
}

const void Skeleton::Render(sf::RenderTarget* target) const
{
	target->draw(m_skeleton);
	target->draw(m_skeletonBoundingRectangle);
}

const void Skeleton::Update(float deltaTime, MapManager& mapManager)
{
	return void();
}

const void Skeleton::Move()
{
	return void();
}
