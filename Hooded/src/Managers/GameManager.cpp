#include "GameManager.hpp"

GameManager::GameManager()
{
	m_windowManager = new WindowManager();
	m_backgroundManager = new BackgroundManager();
	m_mapManager = new MapManager();

	m_backgroundManager->Load();
	m_mapManager->Load(Level::ONE);
	
	m_hooded = new Hooded();
	m_blueHooded = new BlueHooded();
}

GameManager::~GameManager()
{
	delete m_blueHooded;
	delete m_hooded;
	delete m_mapManager;
	delete m_backgroundManager;
	delete m_windowManager;
}

void GameManager::Render()
{
	m_windowManager->m_window->clear(sf::Color(17, 28, 60));

	m_backgroundManager->Render(*m_windowManager->m_window);
	m_mapManager->Render(*m_windowManager->m_window);
	m_blueHooded->Render(m_windowManager->m_window);
	m_hooded->Render(m_windowManager->m_window);

	m_windowManager->m_window->display();
}

const bool GameManager::Running() const
{
	return m_windowManager->m_window->isOpen();
}

void GameManager::Update()
{
	m_deltaTime = (float)m_clock.restart().asMilliseconds();
	std::vector<Entity*> entities = { m_blueHooded };

	m_windowManager->Update(m_deltaTime);
	m_backgroundManager->Update(*m_windowManager->m_camera);
	m_blueHooded->Update(m_deltaTime, *m_mapManager);
	m_hooded->Update(*m_windowManager->m_camera, m_deltaTime, *m_mapManager, entities);
}
 