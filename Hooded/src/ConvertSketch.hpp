#pragma once

#include <array>
#include <SFML/Graphics.hpp>

#include "Enums/Cell.hpp"
#include "Enums/Level.hpp"
#include "GameConfig.hpp"

void ConvertSketch(Map* map, sf::Image mapSketch, unsigned mapSize_X, unsigned mapSize_Y);
