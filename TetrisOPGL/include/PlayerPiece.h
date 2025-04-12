#pragma once

#include "Block.h"
#include "Settings.h"
#include "Tile.h"
#include "Ressource.h"

const int PIECE_SIZE = 4;

class PlayerPiece {

public:
	Block* curBlocks[PIECE_SIZE];
	SHAPE shape;
public:
	PlayerPiece();
	void Spawn(Block(&blocks)[tileWidth * tileHeight], int & nombreBlock, Tile(&board)[tileWidth][tileHeight]);
	bool Down(Tile(&board)[tileWidth][tileHeight]);
};