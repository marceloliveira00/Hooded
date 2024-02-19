#include "GameManager.hpp"

GameManager::GameManager()
{
	windowManager = new WindowManager();
	hooded = new Hooded();
}

GameManager::~GameManager()
{
	delete hooded;
	delete windowManager;
}

void GameManager::Render()
{
	windowManager->m_Window->clear(sf::Color(27, 27, 83));

	hooded->Render(*windowManager->m_Window);

	windowManager->m_Window->display();
}

const bool GameManager::Running() const
{
	return windowManager->m_Window->isOpen();
}

void GameManager::Update()
{
	deltaTime = clock.restart().asMilliseconds(); // Updates delta time

	windowManager->PollEvents();
	windowManager->SetFPS(deltaTime);
	hooded->Update(deltaTime);
}
