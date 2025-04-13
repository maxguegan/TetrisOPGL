#include "Block.h"

Block::Block():posGrille(glm::ivec2(0)){}

void Block::Init(Texture& tex, const float size,Tile & tile) {
	visual.sprite = tex;
	visual.size = glm::vec2(size);
	visual.position = tile.position;
	this->posGrille = tile.gridPosition;
	tile.block = this;
	used = true;
}

void Block::SetPos(Tile& tile) {
	visual.position = tile.position;
	this->posGrille = tile.gridPosition;
	tile.block = this;
	if (tile.block == NULL)
		std::cout << "DANGER Tile x :" << tile.gridPosition.x << " ; y : " << tile.gridPosition.y << std::endl;
}
const glm::ivec2 Block::GetPos() {
	return posGrille;
}
void Block::Render(SpriteRenderer& renderer) {
	visual.draw(renderer);
}