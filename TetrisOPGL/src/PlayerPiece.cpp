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
	this->shape = shape;
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
void PlayerPiece::SwapPiece(Tile(&board)[tileWidth][tileHeight], SHAPE & nextShape) {
	glm::ivec2 curPosition = curBlocks[0]->GetPos();
	std::cout << curPosition.x << " " << curPosition.y << std::endl;
	switch (nextShape)//l'élément 0 est le pivot pour la rotation 
	{
	case SHAPE_SQUARE:

		//block de vérification pour les positions de permutations 
		if (board[curPosition.x][curPosition.y].state == FULL || board[curPosition.x][curPosition.y].state == LIMITE ||
			board[curPosition.x + 1][curPosition.y].state == FULL || board[curPosition.x + 1][curPosition.y].state == LIMITE ||
			board[curPosition.x][curPosition.y + 1].state == FULL || board[curPosition.x][curPosition.y + 1].state == LIMITE ||
			board[curPosition.x + 1][curPosition.y + 1].state == FULL || board[curPosition.x + 1][curPosition.y + 1].state == LIMITE)
			return;
		for (int i = 1; i < PIECE_SIZE; i++)
			board[curBlocks[i]->GetPos().x][curBlocks[i]->GetPos().y].block = nullptr;
		curBlocks[0]->Init(Ressource::GetTexture("block_carre"), tileSize, board[curPosition.x][curPosition.y]);
		curBlocks[1]->Init(Ressource::GetTexture("block_carre"), tileSize, board[curPosition.x + 1][curPosition.y]);
		curBlocks[2]->Init(Ressource::GetTexture("block_carre"), tileSize, board[curPosition.x][curPosition.y + 1]);
		curBlocks[3]->Init(Ressource::GetTexture("block_carre"), tileSize, board[curPosition.x + 1][curPosition.y + 1]);
		break;
	case SHAPE_LINE:
		if (board[curPosition.x][curPosition.y].state == FULL || board[curPosition.x][curPosition.y].state == LIMITE ||
			board[curPosition.x][curPosition.y + 1].state == FULL || board[curPosition.x][curPosition.y + 1].state == LIMITE ||
			board[curPosition.x][curPosition.y + 2].state == FULL || board[curPosition.x][curPosition.y + 2].state == LIMITE ||
			board[curPosition.x][curPosition.y + 3].state == FULL || board[curPosition.x][curPosition.y + 3].state == LIMITE)
			return;
		for (int i = 1; i < PIECE_SIZE; i++)
			board[curBlocks[i]->GetPos().x][curBlocks[i]->GetPos().y].block = nullptr;
		curBlocks[0]->Init(Ressource::GetTexture("block_ligne"), tileSize, board[curPosition.x][curPosition.y + 1]);
		curBlocks[1]->Init(Ressource::GetTexture("block_ligne"), tileSize, board[curPosition.x][curPosition.y]);
		curBlocks[2]->Init(Ressource::GetTexture("block_ligne"), tileSize, board[curPosition.x][curPosition.y + 2]);
		curBlocks[3]->Init(Ressource::GetTexture("block_ligne"), tileSize, board[curPosition.x][curPosition.y + 3]);
		break;
	case SHAPE_T:
		if (board[curPosition.x][curPosition.y].state == FULL || board[curPosition.x][curPosition.y].state == LIMITE ||
			board[curPosition.x + 1][curPosition.y].state == FULL || board[curPosition.x + 1][curPosition.y].state == LIMITE ||
			board[curPosition.x][curPosition.y + 1].state == FULL || board[curPosition.x][curPosition.y + 1].state == LIMITE ||
			board[curPosition.x - 1][curPosition.y].state == FULL || board[curPosition.x - 1][curPosition.y].state == LIMITE)
			return;
		for (int i = 1; i < PIECE_SIZE; i++)
			board[curBlocks[i]->GetPos().x][curBlocks[i]->GetPos().y].block = nullptr;
		curBlocks[0]->Init(Ressource::GetTexture("block_T"), tileSize, board[curPosition.x][curPosition.y]);
		curBlocks[1]->Init(Ressource::GetTexture("block_T"), tileSize, board[curPosition.x + 1][curPosition.y]);
		curBlocks[2]->Init(Ressource::GetTexture("block_T"), tileSize, board[curPosition.x][curPosition.y + 1]);
		curBlocks[3]->Init(Ressource::GetTexture("block_T"), tileSize, board[curPosition.x - 1][curPosition.y]);
		break;
	case SHAPE_L_RIGHT:
		if (board[curPosition.x][curPosition.y + 1].state == FULL || board[curPosition.x][curPosition.y + 1].state == LIMITE ||
			board[curPosition.x][curPosition.y].state == FULL || board[curPosition.x][curPosition.y].state == LIMITE ||
			board[curPosition.x + 1][curPosition.y].state == FULL || board[curPosition.x + 1][curPosition.y].state == LIMITE ||
			board[curPosition.x][curPosition.y + 2].state == FULL || board[curPosition.x][curPosition.y + 2].state == LIMITE)
			return;
		for (int i = 1; i < PIECE_SIZE; i++)
			board[curBlocks[i]->GetPos().x][curBlocks[i]->GetPos().y].block = nullptr;
		curBlocks[0]->Init(Ressource::GetTexture("block_L_droite"), tileSize, board[curPosition.x][curPosition.y + 1]);
		curBlocks[1]->Init(Ressource::GetTexture("block_L_droite"), tileSize, board[curPosition.x][curPosition.y]);
		curBlocks[2]->Init(Ressource::GetTexture("block_L_droite"), tileSize, board[curPosition.x + 1][curPosition.y]);
		curBlocks[3]->Init(Ressource::GetTexture("block_L_droite"), tileSize, board[curPosition.x][curPosition.y + 2]);
		break;
	case SHAPE_L_LEFT:
		if (board[curPosition.x][curPosition.y + 1].state == FULL || board[curPosition.x][curPosition.y + 1].state == LIMITE ||
			board[curPosition.x][curPosition.y].state == FULL || board[curPosition.x][curPosition.y].state == LIMITE ||
			board[curPosition.x - 1][curPosition.y].state == FULL || board[curPosition.x - 1][curPosition.y].state == LIMITE ||
			board[curPosition.x][curPosition.y + 2].state == FULL || board[curPosition.x][curPosition.y + 2].state == LIMITE)
			return;
		for (int i = 1; i < PIECE_SIZE; i++)
			board[curBlocks[i]->GetPos().x][curBlocks[i]->GetPos().y].block = nullptr;
		curBlocks[0]->Init(Ressource::GetTexture("block_L_gauche"), tileSize, board[curPosition.x][curPosition.y + 1]);
		curBlocks[1]->Init(Ressource::GetTexture("block_L_gauche"), tileSize, board[curPosition.x][curPosition.y]);
		curBlocks[2]->Init(Ressource::GetTexture("block_L_gauche"), tileSize, board[curPosition.x - 1][curPosition.y]);
		curBlocks[3]->Init(Ressource::GetTexture("block_L_gauche"), tileSize, board[curPosition.x][curPosition.y + 2]);
		break;
	case SHAPE_Z_RIGHT:
		if (board[curPosition.x][curPosition.y].state == FULL || board[curPosition.x][curPosition.y].state == LIMITE ||
			board[curPosition.x][curPosition.y + 1].state == FULL || board[curPosition.x][curPosition.y + 1].state == LIMITE ||
			board[curPosition.x + 1][curPosition.y + 1].state == FULL || board[curPosition.x + 1][curPosition.y + 1].state == LIMITE ||
			board[curPosition.x - 1][curPosition.y].state == FULL || board[curPosition.x - 1][curPosition.y].state == LIMITE)
			return;
		for (int i = 1; i < PIECE_SIZE; i++)
			board[curBlocks[i]->GetPos().x][curBlocks[i]->GetPos().y].block = nullptr;
		curBlocks[0]->Init(Ressource::GetTexture("block_Z_droite"), tileSize, board[curPosition.x][curPosition.y]);
		curBlocks[1]->Init(Ressource::GetTexture("block_Z_droite"), tileSize, board[curPosition.x][curPosition.y + 1]);
		curBlocks[2]->Init(Ressource::GetTexture("block_Z_droite"), tileSize, board[curPosition.x + 1][curPosition.y + 1]);
		curBlocks[3]->Init(Ressource::GetTexture("block_Z_droite"), tileSize, board[curPosition.x - 1][curPosition.y]);
		break;
	case SHAPE_Z_LEFT:
		if (board[curPosition.x][curPosition.y].state == FULL || board[curPosition.x][curPosition.y].state == LIMITE ||
			board[curPosition.x][curPosition.y + 1].state == FULL || board[curPosition.x][curPosition.y + 1].state == LIMITE ||
			board[curPosition.x - 1][curPosition.y + 1].state == FULL || board[curPosition.x - 1][curPosition.y + 1].state == LIMITE ||
			board[curPosition.x + 1][curPosition.y].state == FULL || board[curPosition.x + 1][curPosition.y].state == LIMITE)
			return;
		for (int i = 1; i < PIECE_SIZE; i++)
			board[curBlocks[i]->GetPos().x][curBlocks[i]->GetPos().y].block = nullptr;
		curBlocks[0]->Init(Ressource::GetTexture("block_Z_gauche"), tileSize, board[curPosition.x][curPosition.y]);
		curBlocks[1]->Init(Ressource::GetTexture("block_Z_gauche"), tileSize, board[curPosition.x][curPosition.y + 1]);
		curBlocks[2]->Init(Ressource::GetTexture("block_Z_gauche"), tileSize, board[curPosition.x - 1][curPosition.y + 1]);
		curBlocks[3]->Init(Ressource::GetTexture("block_Z_gauche"), tileSize, board[curPosition.x + 1][curPosition.y]);
		break;
	default:
		std::cout << "Erreur au niveau du choix de forme" << std::endl;
		break;
	}
	SHAPE temp = shape;
	shape = nextShape;
	nextShape = temp;
}