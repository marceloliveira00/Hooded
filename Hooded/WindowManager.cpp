#include "WindowManager.hpp"
#include <iostream>

WindowManager::WindowManager() : event(new sf::Event())
{
	settings.antialiasingLevel = 8;

	m_Window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Hooded");
	m_Window->setFramerateLimit(144);
}

WindowManager::~WindowManager()
{
	delete event;
	delete m_Window;
}

void WindowManager::PollEvents()
{
	while (m_Window->pollEvent(*event))
	{
		switch (event->type)
		{
		case sf::Event::Closed:
			m_Window->close();
			break;
		}
	}
}

void WindowManager::SetFPS(float deltaTime)
{
	timer += deltaTime;
	if (timer >= 100.f)
	{
		m_Window->setTitle("Hooded - FPS: " + std::to_string(1000 / (int)deltaTime));
		timer = 0.f;
	}
}
