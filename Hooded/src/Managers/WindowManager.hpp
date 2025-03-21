#pragma once

#include <SFML/Graphics.hpp>

#include "../Camera.hpp"
#include "../GameConfig.hpp"

class WindowManager
{
public:
	Camera* m_camera;
	sf::RenderWindow* m_window;

	WindowManager();
	~WindowManager();

	void Update(float deltaTime);

private:
	float timer = 0.f;

	sf::Event* m_event;

	const void PollEvents() const;
	const void SetCameraPos() const;
	void SetFPS(float deltaTime);
};
