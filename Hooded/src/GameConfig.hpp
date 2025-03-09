#pragma once

#include <array>
#include <vector>

#include "Enums/Cell.hpp"
#include "Enums/EntityStatus.hpp"

constexpr unsigned short DEFAULT_SPRITE_SIZE_X_Y = 32;

constexpr unsigned short FRAMERATE = 144;
constexpr unsigned short SCREEN_HEIGHT = 1080;
constexpr unsigned short SCREEN_WIDTH = 1920;

constexpr float GRAVITY = 0.3f;

typedef std::vector<std::array<Cell, SCREEN_HEIGHT>> Map;
/// \brief Stores the row index and the number of sprites in a texture for a given status
/// @param first Number of the row the sprite is in
/// @param second Number of the row the sprite is in
typedef std::map<EntityStatus, std::pair<unsigned short, unsigned short>> SpriteCoordinates;
