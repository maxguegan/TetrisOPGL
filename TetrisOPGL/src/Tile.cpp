#include "Tile.h"
#include "Block.h"
Tile::Tile(glm::vec2 position, glm::ivec2 gridPosition) : position(position), gridPosition(gridPosition), block(NULL), state(EMPTY) {}

Block* Tile::GetBlock() {
	if (state == FULL && block != NULL)
		return block;
	else
		std::cout << "accès à un block dans une case vide : x = " << gridPosition.x << " ; y = " << gridPosition.y << std::endl;
	return NULL;
}