#include "../Headers/BackgroundManager.hpp"

void BackgroundManager::Load()
{
	m_backgroundTexture.loadFromFile("Assets/Maps/Background/Sky_Night.png");
	m_backgroundTexture.setRepeated(true);

	m_background.setTexture(m_backgroundTexture);
	m_background.setScale(1.5, 1.5);
	m_background.setPosition(0, 0);

	m_parallaxShader.loadFromMemory(
		"uniform float offset;"

		"void main() {"
		"    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;"
		"    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;"
		"    gl_TexCoord[0].x = gl_TexCoord[0].x + offset;" // magic
		"    gl_FrontColor = gl_Color;"
		"}"
		, sf::Shader::Vertex);
}

const void BackgroundManager::Render(sf::RenderTarget& target) const
{
	target.draw(m_background, &m_parallaxShader);
}

const void BackgroundManager::Update()
{
	m_parallaxShader.setUniform("offset", m_offset += m_clock.restart().asSeconds() / 500.f);
}
