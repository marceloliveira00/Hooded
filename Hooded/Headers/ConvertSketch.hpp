#pragma once

#include <array>
#include <SFML/Graphics.hpp>

#include "../Headers/Enums/Cell.hpp"
#include "../Headers/Enums/Level.hpp"
#include "../Headers/GameConfig.hpp"

void ConvertSketch(Map* map, sf::Image mapSketch, unsigned mapSize_X, unsigned mapSize_Y);
