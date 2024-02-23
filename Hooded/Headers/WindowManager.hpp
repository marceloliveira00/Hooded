#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../Headers/GameConfig.hpp"

class WindowManager
{
public:
	sf::RenderWindow* m_window;

	WindowManager();
	~WindowManager();

	void PollEvents();
	void SetFPS(float deltaTime);

private:
	float timer = 0.f;
	sf::Event* m_event;
	sf::ContextSettings m_settings;
};
