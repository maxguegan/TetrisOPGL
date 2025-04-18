#include "Game.h"

void CheckIntegrity(Tile(&board)[tileWidth][tileHeight]);

Game::Game(const float width, const float height): SCREEN_WIDTH(width), SCREEN_HEIGHT(height), score(0), nombreBlockBordure(0), state(PLAYING) {
	for (int i = 0; i < 1024; i++) {
		keys[i] = false;
		lockKeys[i] = false;
	}
	nextShape = (SHAPE)(rand() % 7);
}

void Game::Init() {
	InitRessource();
	spriteRenderer.Init(Ressource::GetShader("sprite_shader"));
	glm::mat4 projection = glm::ortho(0.0f, SCREEN_WIDTH, 0.0f, SCREEN_HEIGHT, -1.0f, 1.0f);
	Ressource::GetShader("sprite_shader").setMat4("projection", projection);
	InitMap();
	nextPieceVisual.size = glm::vec2(100.0f);
	nextPieceVisual.position = glm::vec2(SCREEN_WIDTH * 0.75f, SCREEN_HEIGHT * 0.5 - nextPieceVisual.size.x);
	playerPiece.Spawn(blocks, nombreBlockBordure, board, nextShape);
	nextShape = (SHAPE)(rand() % 7);
	SetNewPieceVisual();
}

void Game::InitMap() {
	const float offsetX = (SCREEN_WIDTH - tileWidth * tileSize) / 2.0f ;
	
	//positionne toute les cases de la grille dans la fenêtre 
	for (int i = 0; i < tileHeight; i++) {
		for (int j = 0; j < tileWidth; j++) {
			board[j][i].position = glm::vec2(offsetX + j * tileSize, i * tileSize);
			board[j][i].gridPosition = glm::ivec2(j, i);
			if ((i == 0 || j == 0 || j == tileWidth - 1) && i <= 21) {
				blocks[nombreBlockBordure].Init(Ressource::GetTexture("block_limite"), tileSize, board[j][i]);
				board[j][i].state = FULL;
				nombreBlockBordure++;
			}
				
		}
		
	}
}

void Game::InitRessource() {
	Ressource::LoadShader(std::filesystem::path{ "../shader/SpriteShader.vs" }.string().c_str(), NULL, std::filesystem::path{"../shader/SpriteShader.fs"}.string().c_str(), "sprite_shader");
	Ressource::LoadTexture(std::filesystem::path{ "../texture/block_limite.png" }.string().c_str(), false, "block_limite");
	Ressource::LoadTexture(std::filesystem::path{ "../texture/block_carre.png" }.string().c_str(), false, "block_carre");
	Ressource::LoadTexture(std::filesystem::path{ "../texture/block_ligne.png" }.string().c_str(), false, "block_ligne");
	Ressource::LoadTexture(std::filesystem::path{ "../texture/block_T.png" }.string().c_str(), false, "block_T");
	Ressource::LoadTexture(std::filesystem::path{ "../texture/block_L_droite.png" }.string().c_str(), false, "block_L_droite");
	Ressource::LoadTexture(std::filesystem::path{ "../texture/block_L_gauche.png" }.string().c_str(), false, "block_L_gauche");
	Ressource::LoadTexture(std::filesystem::path{ "../texture/block_Z_droite.png" }.string().c_str(), false, "block_Z_droite");
	Ressource::LoadTexture(std::filesystem::path{ "../texture/block_Z_gauche.png" }.string().c_str(), false, "block_Z_gauche");
	Ressource::LoadTexture(std::filesystem::path{ "../texture/forme_carre.png" }.string().c_str(), false, "forme_carre");
	Ressource::LoadTexture(std::filesystem::path{ "../texture/forme_ligne.png" }.string().c_str(), false, "forme_ligne");
	Ressource::LoadTexture(std::filesystem::path{ "../texture/forme_T.png" }.string().c_str(), false, "forme_T");
	Ressource::LoadTexture(std::filesystem::path{ "../texture/forme_L_droite.png" }.string().c_str(), false, "forme_L_droite");
	Ressource::LoadTexture(std::filesystem::path{ "../texture/forme_L_gauche.png" }.string().c_str(), false, "forme_L_gauche");
	Ressource::LoadTexture(std::filesystem::path{ "../texture/forme_Z_droite.png" }.string().c_str(), false, "forme_Z_droite");
	Ressource::LoadTexture(std::filesystem::path{ "../texture/forme_Z_gauche.png" }.string().c_str(), false, "forme_Z_gauche");

}
void Game::Update(float deltaTime) {
	timer -= deltaTime;
	if (timer < 0.0f && !keys[GLFW_KEY_S]) {
		if (playerPiece.Down(board))
			NewPiece();
			
		timer = maxTimer;
	}
}
void Game::CheckRows() {
	bool clear;
	for (int i = 1; i < tileHeight - 4; i++) {
		clear = true;
		for (int j = 1; j < tileWidth - 1; j++) {
			if (board[j][i].state == EMPTY) {
				clear = false;
				break;
			}
		}

		if (clear) {
			CheckIntegrity(board);
			ClearRow(i);
			CheckRows();
		}
			
	}
	
}
void Game::ClearRow(int row) {
	for (int i = 1; i < tileWidth - 1; i++) {
		board[i][row].GetBlock()->used = false;
		board[i][row].state = EMPTY;
		board[i][row].block = NULL;
	}
	for (int i = row + 1; i < tileHeight - 4; i++) {
		for (int j = 1; j < tileWidth - 1; j++) {
			if (board[j][i].state == FULL) {
				board[j][i].GetBlock()->SetPos(board[j][i - 1]);
				board[j][i].state = EMPTY;
				board[j][i - 1].state = FULL;
				board[j][i].block = NULL;
			}
		}
	}

		
}
void Game::CheckGameOver() {
	for (int i = 1; i < tileWidth - 1; i++) {
		for (int j = tileHeight - 3; j < tileHeight; j++) {
			if (board[i][j].state == FULL)
				state = OVER;
		}
	}
}

void Game::ProcessInput(float deltaTime) {
	if (keys[GLFW_KEY_S]) {
		inputTimer -= deltaTime;
		if (inputTimer <= 0.0f) {
			inputTimer = maxInputTimer;
			if (playerPiece.Down(board)) 
				NewPiece();
		}

	}
	if (keys[GLFW_KEY_D] && !lockKeys[GLFW_KEY_D]) {
		playerPiece.MoveRight(board);
		lockKeys[GLFW_KEY_D] = true;
	}
	else if (!keys[GLFW_KEY_D] && lockKeys[GLFW_KEY_D]) {
		lockKeys[GLFW_KEY_D] = false;
	}
	if (keys[GLFW_KEY_A] && !lockKeys[GLFW_KEY_A]) {
		playerPiece.MoveLeft(board);
		lockKeys[GLFW_KEY_A] = true;
	}
	else if (!keys[GLFW_KEY_A] && lockKeys[GLFW_KEY_A]) {
		lockKeys[GLFW_KEY_A] = false;
	}
	if (keys[GLFW_KEY_E] && !lockKeys[GLFW_KEY_E]) {
		playerPiece.RotateRight(board);
		lockKeys[GLFW_KEY_E] = true;
	}
	else if (!keys[GLFW_KEY_E] && lockKeys[GLFW_KEY_E]) {
		lockKeys[GLFW_KEY_E] = false;
	}
	if (keys[GLFW_KEY_Q] && !lockKeys[GLFW_KEY_Q]) {
		playerPiece.RotateLeft(board);
		lockKeys[GLFW_KEY_Q] = true;
	}
	else if (!keys[GLFW_KEY_Q] && lockKeys[GLFW_KEY_Q]) {
		lockKeys[GLFW_KEY_Q] = false;
	}
}

void Game::Render() {
	
	for(int i = 0; i < tileHeight * tileWidth; i++)
		if(blocks[i].used)
			blocks[i].Render(spriteRenderer);
	nextPieceVisual.draw(spriteRenderer);
}
void Game::SetNewPieceVisual() {
	switch (nextShape)
	{
	case SHAPE_SQUARE:
		nextPieceVisual.sprite = Ressource::GetTexture("forme_carre");
		break;
	case SHAPE_LINE:
		nextPieceVisual.sprite = Ressource::GetTexture("forme_ligne");
		break;
	case SHAPE_T:
		nextPieceVisual.sprite = Ressource::GetTexture("forme_T");
		break;
	case SHAPE_L_RIGHT:
		nextPieceVisual.sprite = Ressource::GetTexture("forme_L_droite");
		break;
	case SHAPE_L_LEFT:
		nextPieceVisual.sprite = Ressource::GetTexture("forme_L_gauche");
		break;
	case SHAPE_Z_RIGHT:
		nextPieceVisual.sprite = Ressource::GetTexture("forme_Z_droite");
		break;
	case SHAPE_Z_LEFT:
		nextPieceVisual.sprite = Ressource::GetTexture("forme_Z_gauche");
		break;
	default:
		break;
	}
}


void Game::NewPiece(){
	CheckIntegrity(board);
	CheckRows();
	CheckGameOver();
	playerPiece.Spawn(blocks, nombreBlockBordure, board,nextShape);
	nextShape = nextShape = (SHAPE)(rand() % 7);
	SetNewPieceVisual();
}

bool Game::IsOver() {
	return state == OVER;
}

void CheckIntegrity(Tile(&board)[tileWidth][tileHeight]) {
	for (int i = 0; i < tileWidth; i++) {
		for (int j = 0; j < tileHeight; j++) {
			if (board[i][j].state == FULL && board[i][j].block == NULL)
				std::cout << "GROS PROBLEME x : " << i << " ; y : " << j << std::endl;
		}
	}
}