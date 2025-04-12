#pragma once

#include <glm/glm.hpp>

enum State
{
	EMPTY,
	FULL
	
};
struct Tile
{
	
	State state;
	glm::vec2 position;
	glm::ivec2 gridPosition;
	Tile(glm::vec2 position = glm::vec2(0.0f), glm::ivec2 gridPosition = glm::ivec2(0));
};

