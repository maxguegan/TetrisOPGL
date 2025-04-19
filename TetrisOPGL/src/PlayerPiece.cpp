#include "PlayerPiece.h"

PlayerPiece::PlayerPiece(){
	
	for (int i = 0; i < PIECE_SIZE; i++)
		curBlocks[i] = NULL;
}
void PlayerPiece::Spawn(Block* blocks, int nombreBlockLimite,Tile(&board)[tileWidth][tileHeight], SHAPE shape) {
	int j = 0;
	for (int i = nombreBlockLimite; i < tileHeight * tileWidth; i++) {
		if (!blocks[i].used) {
			curBlocks[j] = &blocks[i]; //Récupère les 4 prochains blocks dans la liste pour la pièce 
			j++;
			if (j == 4)
				break;
		}
			
	}
		
	int heightLimit = tileHeight - 5;
	int gridMiddle = tileWidth / 2;

	switch (shape)//l'élément 0 est le pivot pour la rotation 
	{
	case SHAPE_SQUARE:
		curBlocks[0]->Init(Ressource::GetTexture("block_carre"), tileSize, board[gridMiddle][heightLimit]);
		curBlocks[1]->Init(Ressource::GetTexture("block_carre"), tileSize, board[gridMiddle + 1][heightLimit]);
		curBlocks[2]->Init(Ressource::GetTexture("block_carre"), tileSize, board[gridMiddle][heightLimit + 1]);
		curBlocks[3]->Init(Ressource::GetTexture("block_carre"), tileSize, board[gridMiddle + 1][heightLimit + 1]);
		break;
	case SHAPE_LINE:
		curBlocks[0]->Init(Ressource::GetTexture("block_ligne"), tileSize, board[gridMiddle][heightLimit + 1]);
		curBlocks[1]->Init(Ressource::GetTexture("block_ligne"), tileSize, board[gridMiddle][heightLimit]);
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
}

//Renvoie vrai si on tente de descendre alors que l'un des blocks est en contact avec un block déjà placé et faux sinon
bool PlayerPiece::Down(Tile(&board)[tileWidth][tileHeight]) {
	
	for (int i = 0; i < PIECE_SIZE; i++) {
		glm::ivec2 blockPos = curBlocks[i]->GetPos();
		// On vérifie si la prochaine case est déjà remplie, si oui on arrète et on renvoie vrai	
		if (board[blockPos.x][blockPos.y - 1].state == FULL || board[blockPos.x][blockPos.y - 1].state == LIMITE) {
			this->AffixPiece(board);
			return true;
		}
	}
	for (int i = 0; i < PIECE_SIZE; i++) {
		glm::ivec2 blockPos = curBlocks[i]->GetPos();
		board[blockPos.x][blockPos.y].block = NULL;
		curBlocks[i]->SetPos(board[blockPos.x][blockPos.y - 1]);
	}
	return false;
}
void PlayerPiece::MoveRight(Tile(&board)[tileWidth][tileHeight]) {
	for (int i = 0; i < PIECE_SIZE; i++) {
		glm::ivec2 blockPos = curBlocks[i]->GetPos();
		// On vérifie si la prochaine case est déjà remplie, si oui on arrète et on renvoie vrai	
		if (board[blockPos.x + 1][blockPos.y].state == FULL || board[blockPos.x + 1][blockPos.y].state == LIMITE) {
			return;
		}
	}
	for (int i = 0; i < PIECE_SIZE; i++) {
		glm::ivec2 blockPos = curBlocks[i]->GetPos();
		board[blockPos.x][blockPos.y].block = NULL;
		curBlocks[i]->SetPos(board[blockPos.x + 1][blockPos.y]);
	}
	
}
void PlayerPiece::MoveLeft(Tile(&board)[tileWidth][tileHeight]) {
	for (int i = 0; i < PIECE_SIZE; i++) {
		glm::ivec2 blockPos = curBlocks[i]->GetPos();
		// On vérifie si la prochaine case est déjà remplie, si oui on arrète et on renvoie vrai	
		if (board[blockPos.x - 1][blockPos.y].state == FULL || board[blockPos.x - 1][blockPos.y].state == LIMITE) {
			return;
		}
	}
	for (int i = 0; i < PIECE_SIZE; i++) {
		glm::ivec2 blockPos = curBlocks[i]->GetPos();
		board[blockPos.x][blockPos.y].block = NULL;
		curBlocks[i]->SetPos(board[blockPos.x - 1][blockPos.y]);
	}
}
void PlayerPiece::AffixPiece(Tile(&board)[tileWidth][tileHeight]) {
	for (int i = 0; i < PIECE_SIZE; i++) {
		glm::ivec2 blockPos = curBlocks[i]->GetPos();
		curBlocks[i]->SetPos(board[blockPos.x][blockPos.y]);
		board[blockPos.x][blockPos.y].state = FULL;
	}
}

void PlayerPiece::RotateRight(Tile(&board)[tileWidth][tileHeight]) {
	glm::ivec2 pivotPos = curBlocks[0]->GetPos();
	for (int i = 1; i < PIECE_SIZE; i++) {
		glm::ivec2 blockPos = curBlocks[i]->GetPos();
		int rotateY = -(blockPos.x - pivotPos.x);
		int rotateX = blockPos.y - pivotPos.y;
		if (board[pivotPos.x + rotateX][pivotPos.y + rotateY].state == FULL || board[blockPos.x + rotateX][blockPos.y + rotateY].state == LIMITE)
			return;
	}
	for (int i = 1; i < PIECE_SIZE; i++) {
		glm::ivec2 blockPos = curBlocks[i]->GetPos();
		board[blockPos.x][blockPos.y].block = NULL;
		int rotateY = -(blockPos.x - pivotPos.x);
		int rotateX = blockPos.y - pivotPos.y;

		curBlocks[i]->SetPos(board[pivotPos.x + rotateX][pivotPos.y + rotateY]);
	}
	
}
void PlayerPiece::RotateLeft(Tile(&board)[tileWidth][tileHeight]) {
	glm::ivec2 pivotPos = curBlocks[0]->GetPos();
	for (int i = 1; i < PIECE_SIZE; i++) {
		glm::ivec2 blockPos = curBlocks[i]->GetPos();
		board[blockPos.x][blockPos.y].block = NULL;
		int rotateY = blockPos.x - pivotPos.x;
		int rotateX = -(blockPos.y - pivotPos.y);
		if (board[pivotPos.x + rotateX][pivotPos.y + rotateY].state == FULL || board[blockPos.x + rotateX][blockPos.y + rotateY].state == LIMITE)
			return;
	}
	for (int i = 1; i < PIECE_SIZE; i++) {
		glm::ivec2 blockPos = curBlocks[i]->GetPos();
		int rotateY = blockPos.x - pivotPos.x;
		int rotateX = -(blockPos.y - pivotPos.y);
		curBlocks[i]->SetPos(board[pivotPos.x + rotateX][pivotPos.y + rotateY]);
	}
}