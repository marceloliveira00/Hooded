#pragma once

#include <array>
#include <vector>

#include "../Headers/Enums/Cell.hpp"

constexpr unsigned short DEFAULT_SPRITE_SIZE_X_Y = 32;

constexpr unsigned short FRAMERATE = 144;
constexpr unsigned short SCREEN_HEIGHT = 1080;
constexpr unsigned short SCREEN_WIDTH = 1920;

constexpr float GRAVITY = 0.3f;

typedef std::vector<std::array<Cell, SCREEN_HEIGHT>> Map;