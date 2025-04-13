#pragma once

#include <glm/glm.hpp>


class Block;

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
	Block * block;
	Tile(glm::vec2 position = glm::vec2(0.0f), glm::ivec2 gridPosition = glm::ivec2(0));
	Block* GetBlock();
};

