#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "GameConfig.hpp"

class WindowManager
{
public:
	sf::RenderWindow* m_Window;

	WindowManager();
	~WindowManager();

	void PollEvents();
	void SetFPS(float deltaTime);

private:
	float timer = 0.f;
	sf::Event* event;
	sf::ContextSettings settings;
};
