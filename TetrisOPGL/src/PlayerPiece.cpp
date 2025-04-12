#include "PlayerPiece.h"

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
		
	
	shape = static_cast<SHAPE>(rand() % 7);
	shape = SHAPE::SHAPE_SQUARE;
	switch (shape)
	{
	case SHAPE_SQUARE:
		curBlocks[0]->Init(Ressource::GetTexture("block_carre"), tileSize, board[6][22], glm::ivec2(6, 22));
		curBlocks[1]->Init(Ressource::GetTexture("block_carre"), tileSize, board[7][22], glm::ivec2(7, 22));
		curBlocks[2]->Init(Ressource::GetTexture("block_carre"), tileSize, board[6][23], glm::ivec2(6, 23));
		curBlocks[3]->Init(Ressource::GetTexture("block_carre"), tileSize, board[7][23], glm::ivec2(7, 23));
		break;
	case SHAPE_LINE:
		break;
	case SHAPE_T:
		break;
	case SHAPE_L_RIGHT:
		break;
	case SHAPE_L_LEFT:
		break;
	case SHAPE_Z_RIGHT:
		break;
	case SHAPE_Z_LEFT:
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
		if (board[blockPos.x][blockPos.y - 1].state == FULL)// On vérifie si la prochaine case est déjà remplie, si oui on arrète et 
			return true;											//on renvoie vrai	
	}
	for (int i = 0; i < PIECE_SIZE; i++) {
		glm::ivec2 blockPos = curBlocks[i]->GetPos();
		curBlocks[i]->SetPos(board[blockPos.x][blockPos.y - 1], glm::ivec2(blockPos.x, blockPos.y - 1));
	}
	return false;
}