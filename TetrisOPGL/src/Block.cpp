#include "Block.h"

Block::Block():posGrille(glm::ivec2(0)){}

void Block::Init(Texture& tex, const float size,Tile & tile, glm::ivec2 posGrille) {
	visual.sprite = &tex;
	visual.size = glm::vec2(size);
	visual.position = tile.position;
	this->posGrille = posGrille;
}

void Block::SetPos(Tile& tile, glm::ivec2 posGrille) {
	visual.position = tile.position;
	this->posGrille = posGrille;
}
glm::ivec2 Block::GetPos() {
	return posGrille;
}
void Block::Render(SpriteRenderer& renderer) {
	visual.draw(renderer);
}