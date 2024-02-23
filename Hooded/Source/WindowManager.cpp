#include "../Headers/WindowManager.hpp"

WindowManager::WindowManager() : m_event(new sf::Event())
{
	m_settings.antialiasingLevel = 8;

	m_window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Hooded");
	m_window->setFramerateLimit(FRAMERATE);
}

WindowManager::~WindowManager()
{
	delete m_event;
	delete m_window;
}

void WindowManager::PollEvents()
{
	while (m_window->pollEvent(*m_event))
	{
		switch (m_event->type)
		{
		case sf::Event::Closed:
			m_window->close();
			break;
		}
	}
}

void WindowManager::SetFPS(float deltaTime)
{
	timer += deltaTime;
	if (timer >= 100.f)
	{
		m_window->setTitle("Hooded - FPS: " + std::to_string(1000 / (int)deltaTime));
		timer = 0.f;
	}
}
