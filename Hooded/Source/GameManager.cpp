#include "../Headers/GameManager.hpp"
#include "../Assets/Maps/LevelSketch.hpp"

GameManager::GameManager()
{
	m_windowManager = new WindowManager();
	m_mapManager = new MapManager();
	m_mapManager->Load(Level::ONE);
	
	m_hooded = new Hooded();
}

GameManager::~GameManager()
{
	delete m_hooded;
	delete m_mapManager;
	delete m_windowManager;
}

void GameManager::Render()
{
	m_windowManager->m_window->clear(sf::Color(27, 27, 83));

	m_mapManager->Render(m_windowManager->m_window);
	m_hooded->Render(m_windowManager->m_window);

	m_windowManager->m_window->display();
}

const bool GameManager::Running() const
{
	return m_windowManager->m_window->isOpen();
}

void GameManager::Update()
{
	m_deltaTime = (float)m_clock.restart().asMilliseconds(); // Updates delta time

	m_windowManager->Update(m_deltaTime);

	m_mapManager->Update();

	m_hooded->Update(m_windowManager->m_camera, m_deltaTime);
}
 