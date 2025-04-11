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
	Tile(glm::vec2 position = glm::vec2(0.0f));
};

