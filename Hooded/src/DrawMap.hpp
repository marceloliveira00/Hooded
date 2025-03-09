#pragma once

#include <SFML/Graphics.hpp>

#include "Enums/Cell.hpp"
#include "GameConfig.hpp"

void DrawMap(const Map* map, sf::Image& mapSketch, sf::Texture& mapTexture, sf::Texture& m_mapPropsTexture, sf::RenderTarget& target);
