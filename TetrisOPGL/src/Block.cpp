#include "Block.h"

Block::Block():posGrilleX(0), posGrilleY(0){}

void Block::Init(Texture& tex, const float size,Tile & tile) {
	visual.sprite = &tex;
	visual.size = glm::vec2(size);
	visual.position = tile.position;
	tile.state = FULL;
}

void Block::SetPos(Tile& tile) {
	visual.position = tile.position;
	tile.state = FULL;
}

void Block::Render(SpriteRenderer& renderer) {
	visual.draw(renderer);
}