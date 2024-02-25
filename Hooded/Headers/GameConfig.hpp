#pragma once

#include <array>
#include <vector>

#include "../Headers/Enums/Cell.hpp"

constexpr unsigned short DEFAULT_SPRITE_SIZE = 32;

constexpr unsigned short FRAMERATE = 144;
constexpr unsigned short SCREEN_HEIGHT = 1080;
constexpr unsigned short SCREEN_WIDTH = 1920;

typedef std::vector<std::array<Cell, SCREEN_HEIGHT / DEFAULT_SPRITE_SIZE>> Map;