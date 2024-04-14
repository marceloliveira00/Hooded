#include "../Headers/BackgroundManager.hpp"

void BackgroundManager::Load()
{
	m_backgroundTexture.loadFromFile("Assets/Maps/Background/Sky_Night.png");

	m_background.setTexture(m_backgroundTexture);
	m_background.setScale(1.5, 1.5);
	m_background.setPosition(0, 0);
}

const void BackgroundManager::Render(sf::RenderTarget& target) const
{
	target.draw(m_background);
}
