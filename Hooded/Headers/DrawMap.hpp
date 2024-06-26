#pragma once

#include <SFML/Graphics.hpp>

#include "../Headers/Enums/Cell.hpp"
#include "../Headers/GameConfig.hpp"

void DrawMap(const Map* map, sf::Image& mapSketch, sf::Texture& mapTexture, sf::Texture& m_mapPropsTexture, sf::RenderTarget& target);
