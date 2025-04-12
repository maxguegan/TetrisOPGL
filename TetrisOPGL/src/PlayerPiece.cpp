﻿#include "PlayerPiece.h"

PlayerPiece::PlayerPiece(){
	shape = SHAPE::SHAPE_LINE;
	for (int i = 0; i < PIECE_SIZE; i++)
		curBlocks[i] = NULL;
}
void PlayerPiece::Spawn(Block(&blocks)[tileWidth * tileHeight], int & nombreBlock,Tile(&board)[tileWidth][tileHeight]) {
	int j = 0;
	for (int i = nombreBlock; i < PIECE_SIZE + nombreBlock; i++) {
		curBlocks[j] = &blocks[i]; //Récupère les 4 prochains blocks dans la liste pour la pièce 
		j++;
	}
		
	int heightLimit = tileHeight - 4;
	int gridMiddle = tileWidth / 2;
	shape = static_cast<SHAPE>(rand() % 7);
	switch (shape)//l'élément 0 est le pivot pour la rotation 
	{
	case SHAPE_SQUARE:
		curBlocks[0]->Init(Ressource::GetTexture("block_carre"), tileSize, board[gridMiddle][heightLimit]);
		curBlocks[1]->Init(Ressource::GetTexture("block_carre"), tileSize, board[gridMiddle + 1][heightLimit]);
		curBlocks[2]->Init(Ressource::GetTexture("block_carre"), tileSize, board[gridMiddle][heightLimit + 1]);
		curBlocks[3]->Init(Ressource::GetTexture("block_carre"), tileSize, board[gridMiddle + 1][heightLimit + 1]);
		break;
	case SHAPE_LINE:
		curBlocks[0]->Init(Ressource::GetTexture("block_ligne"), tileSize, board[gridMiddle][heightLimit]);
		curBlocks[1]->Init(Ressource::GetTexture("block_ligne"), tileSize, board[gridMiddle][heightLimit + 1]);
		curBlocks[2]->Init(Ressource::GetTexture("block_ligne"), tileSize, board[gridMiddle][heightLimit + 2]);
		curBlocks[3]->Init(Ressource::GetTexture("block_ligne"), tileSize, board[gridMiddle][heightLimit + 3]);
		break;
	case SHAPE_T:
		curBlocks[0]->Init(Ressource::GetTexture("block_T"), tileSize, board[gridMiddle][heightLimit]);
		curBlocks[1]->Init(Ressource::GetTexture("block_T"), tileSize, board[gridMiddle + 1][heightLimit]);
		curBlocks[2]->Init(Ressource::GetTexture("block_T"), tileSize, board[gridMiddle][heightLimit + 1]);
		curBlocks[3]->Init(Ressource::GetTexture("block_T"), tileSize, board[gridMiddle - 1][heightLimit]);
		break;
	case SHAPE_L_RIGHT:
		curBlocks[0]->Init(Ressource::GetTexture("block_L_droite"), tileSize, board[gridMiddle][heightLimit + 1]);
		curBlocks[1]->Init(Ressource::GetTexture("block_L_droite"), tileSize, board[gridMiddle][heightLimit]);
		curBlocks[2]->Init(Ressource::GetTexture("block_L_droite"), tileSize, board[gridMiddle + 1][heightLimit]);
		curBlocks[3]->Init(Ressource::GetTexture("block_L_droite"), tileSize, board[gridMiddle][heightLimit + 2]);
		break;
	case SHAPE_L_LEFT:
		curBlocks[0]->Init(Ressource::GetTexture("block_L_gauche"), tileSize, board[gridMiddle][heightLimit + 1]);
		curBlocks[1]->Init(Ressource::GetTexture("block_L_gauche"), tileSize, board[gridMiddle][heightLimit]);
		curBlocks[2]->Init(Ressource::GetTexture("block_L_gauche"), tileSize, board[gridMiddle - 1][heightLimit]);
		curBlocks[3]->Init(Ressource::GetTexture("block_L_gauche"), tileSize, board[gridMiddle][heightLimit + 2]);
		break;
	case SHAPE_Z_RIGHT:
		curBlocks[0]->Init(Ressource::GetTexture("block_Z_droite"), tileSize, board[gridMiddle][heightLimit]);
		curBlocks[1]->Init(Ressource::GetTexture("block_Z_droite"), tileSize, board[gridMiddle][heightLimit + 1]);
		curBlocks[2]->Init(Ressource::GetTexture("block_Z_droite"), tileSize, board[gridMiddle + 1][heightLimit + 1]);
		curBlocks[3]->Init(Ressource::GetTexture("block_Z_droite"), tileSize, board[gridMiddle - 1][heightLimit]);
		break;
	case SHAPE_Z_LEFT:
		curBlocks[0]->Init(Ressource::GetTexture("block_Z_gauche"), tileSize, board[gridMiddle][heightLimit]);
		curBlocks[1]->Init(Ressource::GetTexture("block_Z_gauche"), tileSize, board[gridMiddle][heightLimit + 1]);
		curBlocks[2]->Init(Ressource::GetTexture("block_Z_gauche"), tileSize, board[gridMiddle - 1][heightLimit + 1]);
		curBlocks[3]->Init(Ressource::GetTexture("block_Z_gauche"), tileSize, board[gridMiddle + 1][heightLimit]);
		break;
	default:
		std::cout << "Erreur au niveau du choix de forme" << std::endl;
		break;
	}
	nombreBlock += 4;
}

//Renvoie vrai si on tente de descendre alors que l'un des blocks est en contact avec un block déjà placé et faux sinon
bool PlayerPiece::Down(Tile(&board)[tileWidth][tileHeight]) {
	
	for (int i = 0; i < PIECE_SIZE; i++) {
		glm::ivec2 blockPos = curBlocks[i]->GetPos();
		// On vérifie si la prochaine case est déjà remplie, si oui on arrète et on renvoie vrai	
		if (board[blockPos.x][blockPos.y - 1].state == FULL) {
			this->AffixPiece(board);
			return true;
		}
	}
	for (int i = 0; i < PIECE_SIZE; i++) {
		glm::ivec2 blockPos = curBlocks[i]->GetPos();
		curBlocks[i]->SetPos(board[blockPos.x][blockPos.y - 1]);
	}
	return false;
}
void PlayerPiece::MoveRight(Tile(&board)[tileWidth][tileHeight]) {
	for (int i = 0; i < PIECE_SIZE; i++) {
		glm::ivec2 blockPos = curBlocks[i]->GetPos();
		// On vérifie si la prochaine case est déjà remplie, si oui on arrète et on renvoie vrai	
		if (board[blockPos.x + 1][blockPos.y].state == FULL) {
			return;
		}
	}
	for (int i = 0; i < PIECE_SIZE; i++) {
		glm::ivec2 blockPos = curBlocks[i]->GetPos();
		curBlocks[i]->SetPos(board[blockPos.x + 1][blockPos.y]);
	}
	
}
void PlayerPiece::MoveLeft(Tile(&board)[tileWidth][tileHeight]) {
	for (int i = 0; i < PIECE_SIZE; i++) {
		glm::ivec2 blockPos = curBlocks[i]->GetPos();
		// On vérifie si la prochaine case est déjà remplie, si oui on arrète et on renvoie vrai	
		if (board[blockPos.x - 1][blockPos.y].state == FULL) {
			return;
		}
	}
	for (int i = 0; i < PIECE_SIZE; i++) {
		glm::ivec2 blockPos = curBlocks[i]->GetPos();
		curBlocks[i]->SetPos(board[blockPos.x - 1][blockPos.y]);
	}
}
void PlayerPiece::AffixPiece(Tile(&board)[tileWidth][tileHeight]) {
	for (int i = 0; i < PIECE_SIZE; i++) {
		glm::ivec2 blockPos = curBlocks[i]->GetPos();
		board[blockPos.x][blockPos.y].state = FULL;
	}
}
