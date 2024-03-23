#pragma once

#include <array>
#include <SFML/Graphics.hpp>

#include "../Headers/Enums/Cell.hpp"
#include "../Headers/GameConfig.hpp"

void DrawMap(const Map* map, sf::Image* mapSketch, sf::Texture* mapTexture, sf::RenderTarget& target);
