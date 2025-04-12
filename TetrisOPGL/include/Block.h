#pragma once

#include <glm/common.hpp>
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Tile.h"
#include "Texture.h"

enum SHAPE
{
	SHAPE_SQUARE,
	SHAPE_LINE,
	SHAPE_T,
	SHAPE_L_RIGHT,
	SHAPE_L_LEFT,
	SHAPE_Z_RIGHT,
	SHAPE_Z_LEFT
};


class Block {
public:
	GameObject visual;
	
public:
	Block();
	void Init(Texture & tex, const float size, Tile & tile, glm::ivec2 posGrille);
	void SetPos(Tile & tile, glm::ivec2 posGrille);
	glm::ivec2 GetPos();
	void Render(SpriteRenderer & renderer);

	
private:
	glm::ivec2 posGrille;
};