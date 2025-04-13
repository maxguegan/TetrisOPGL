﻿#pragma once

#include "Block.h"
#include "Settings.h"
#include "Tile.h"
#include "Ressource.h"

const int PIECE_SIZE = 4;

class PlayerPiece {

public:
	Block* curBlocks[PIECE_SIZE];
	SHAPE shape, nextShape;
public:
	PlayerPiece();
	void Spawn(Block(&blocks)[tileWidth * tileHeight], int nombreBlockLimite, Tile(&board)[tileWidth][tileHeight]);
	bool Down(Tile(&board)[tileWidth][tileHeight]);
	void MoveRight(Tile(&board)[tileWidth][tileHeight]);
	void MoveLeft(Tile(&board)[tileWidth][tileHeight]);
	void RotateRight(Tile(&board)[tileWidth][tileHeight]);
	void RotateLeft(Tile(&board)[tileWidth][tileHeight]);
	void AffixPiece(Tile(&board)[tileWidth][tileHeight]);//Fin de traitement d'une pièce qui est bloqué 

};