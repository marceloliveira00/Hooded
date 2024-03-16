#include "../Headers/WindowManager.hpp"

WindowManager::WindowManager() : m_event(new sf::Event())
{
	m_camera = new Camera();

	m_window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Hooded");
	m_window->setFramerateLimit(FRAMERATE);
}

WindowManager::~WindowManager()
{
	delete m_event;
	delete m_camera;
	delete m_window;
}

void WindowManager::Update(float deltaTime)
{
	PollEvents();
	//SetFPS(deltaTime);
	SetCameraPos();
}

const void WindowManager::PollEvents() const
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

const void WindowManager::SetCameraPos() const
{
	m_window->setView(m_camera->GetCameraView());
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
