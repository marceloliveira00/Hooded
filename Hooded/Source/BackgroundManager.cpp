#include "../Headers/BackgroundManager.hpp"

void BackgroundManager::Load()
{
	m_skyTexture.loadFromFile("Assets/Maps/Background/Sky_Night.png");
	m_lightedCloudsTexture.loadFromFile("Assets/Maps/Background/Clouds_Night_Moonlited.png");
	m_cloudsTexture.loadFromFile("Assets/Maps/Background/Clouds_Night.png");

	m_skyTexture.setRepeated(true);
	m_lightedCloudsTexture.setRepeated(true);
	m_cloudsTexture.setRepeated(true);

	m_sky.setTexture(m_skyTexture);
	m_lightedClouds.setTexture(m_lightedCloudsTexture);
	m_clouds.setTexture(m_cloudsTexture);

	m_backgroundHalfWidth = m_skyTexture.getSize().x / 2.f;

	m_parallaxShader.loadFromMemory(
		"uniform float offset;"

		"void main() {"
		"    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;"
		"    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;"
		"    gl_TexCoord[0].x = gl_TexCoord[0].x + offset;"
		"    gl_FrontColor = gl_Color;"
		"}"
		, sf::Shader::Vertex);
}

const void BackgroundManager::Render(sf::RenderTarget& target) const
{
	target.draw(m_sky);
	target.draw(m_clouds, &m_parallaxShader);
	target.draw(m_lightedClouds, &m_parallaxShader);
}

const void BackgroundManager::Update(Camera& camera)
{
	m_sky.setPosition(camera.GetCameraView().getCenter().x - m_backgroundHalfWidth, 0.f);
	m_lightedClouds.setPosition(camera.GetCameraView().getCenter().x - m_backgroundHalfWidth, 150.f);
	m_clouds.setPosition(camera.GetCameraView().getCenter().x - m_backgroundHalfWidth, 50.f);

	// moves the background while the camera moves
	m_offset += m_clock.restart().asMilliseconds() / 20.f;
	m_parallaxShader.setUniform("offset", (camera.GetCameraView().getCenter().x + m_offset) / 5000.f);
}
