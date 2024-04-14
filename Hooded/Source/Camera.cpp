#include "../Headers/Camera.hpp"

Camera::Camera(float zoomLevel) : m_zoomLevel(zoomLevel)
{

}

const sf::View Camera::GetCameraView() const
{
	const float aspect = (float)(SCREEN_WIDTH) / SCREEN_HEIGHT;

	sf::Vector2f size;
	if (aspect < 1.f) size = sf::Vector2f(m_zoomLevel, m_zoomLevel / aspect);

	else size = sf::Vector2f(m_zoomLevel * aspect, m_zoomLevel);

	return sf::View(m_position, size);
}

const void Camera::SetPosition(const float posX, const float posY)
{
	if (posX <= m_camOffSetX) m_position = sf::Vector2f(m_camOffSetX, posY - 20.f);

	else if (posY >= m_camOffSetY) m_position = sf::Vector2f(posX, m_camOffSetY - 20);

	else m_position = sf::Vector2f(posX, posY - 20.f);
}