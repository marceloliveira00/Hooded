#pragma once

#include <array>
#include <vector>

#include "../Headers/Enums/Cell.hpp"

constexpr float GAME_SCALE = 3.f;

constexpr unsigned short SPRITE_CELL_SIZE = 32;

constexpr unsigned short FRAMERATE = 144;
constexpr unsigned short SCREEN_HEIGHT = 1080;
constexpr unsigned short SCREEN_WIDTH = 1920;

typedef std::vector<std::array<Cell, SCREEN_HEIGHT / SPRITE_CELL_SIZE>> Map;