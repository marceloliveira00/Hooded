#pragma once

#include <SFML/Graphics.hpp>

#include "../Headers/Enums/Cell.hpp"
#include "../Headers/GameConfig.hpp"

bool DrawMapProps(const Map* map, unsigned short x, unsigned short y, unsigned short& rectLeft, unsigned short& rectTop, unsigned short& spriteX, unsigned short& spriteY);
