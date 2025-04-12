#include "Tile.h"

Tile::Tile(glm::vec2 position, glm::ivec2 gridPosition) : position(position), gridPosition(gridPosition), state(EMPTY) {}