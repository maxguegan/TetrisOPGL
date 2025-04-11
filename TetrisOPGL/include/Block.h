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
	void Init(Texture & tex, const float size, Tile & tile);
	void SetPos(Tile & tile);
	void Render(SpriteRenderer & renderer);
	
	
private:
	int posGrilleX;
	int posGrilleY;
};