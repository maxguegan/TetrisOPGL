#include "Game.h"

void CheckIntegrity(Tile(&board)[tileWidth][tileHeight]);

Game::Game(const float width, const float height): SCREEN_WIDTH(width), SCREEN_HEIGHT(height), score(0), level(1), nombreBlockBordure(0), gameState(PLAYING) {
	for (int i = 0; i < 1024; i++) {
		keys[i] = false;
		lockKeys[i] = false;
	}
	nextShape = (SHAPE)(rand() % 7);
}

void Game::Init() {
	InitRessource();
	spriteRenderer = std::make_unique<SpriteRenderer>(Ressource::GetShader("sprite_shader"));
	textRenderer = std::make_unique<TextRenderer>(std::filesystem::path{ "../fonts/arial.ttf" }.string().c_str(), Ressource::GetShader("text_shader"));
	glm::mat4 projection = glm::ortho(0.0f, SCREEN_WIDTH, 0.0f, SCREEN_HEIGHT, -1.0f, 1.0f);
	Ressource::GetShader("sprite_shader").setMat4("projection", projection);
	InitMap();
	InitUI();
	playerPiece.Spawn(blocks.get(), nombreBlockBordure, board, nextShape);
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
			if ((i == 0 || j == 0 || j == tileWidth - 1) ||i == tileHeight - 1) {
				if (i <= 21) {
					blocks[nombreBlockBordure].Init(Ressource::GetTexture("block_limite"), tileSize, board[j][i]);
				}
				else {
					blocks[nombreBlockBordure].Init(Ressource::GetTexture("block_limite_fin"), tileSize, board[j][i]);
				}
				
				board[j][i].state = LIMITE;
				nombreBlockBordure++;
			}
				
		}
		
	}
}

void Game::InitRessource() {
	Ressource::LoadShader(std::filesystem::path{ "../shader/SpriteShader.vs" }.string().c_str(), NULL, std::filesystem::path{"../shader/SpriteShader.fs"}.string().c_str(), "sprite_shader");
	Ressource::LoadShader(std::filesystem::path{ "../shader/TextShader.vs" }.string().c_str(), NULL, std::filesystem::path{ "../shader/TextShader.fs" }.string().c_str(), "text_shader");
	Ressource::LoadTexture(std::filesystem::path{ "../texture/block_limite.png" }.string().c_str(), false, "block_limite");
	Ressource::LoadTexture(std::filesystem::path{ "../texture/block_limite_fin.png" }.string().c_str(), false, "block_limite_fin");
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
void Game::InitUI() {
	nextPieceVisual.size = glm::vec2(100.0f);
	nextPieceVisual.position = glm::vec2(SCREEN_WIDTH * 0.75f, SCREEN_HEIGHT * 0.5 - nextPieceVisual.size.x);
	nextPieceText.chaine = "Next";
	nextPieceText.position = glm::vec2(nextPieceVisual.position.x, nextPieceVisual.position.y + nextPieceVisual.size.y + 50.0f);
	nextPieceText.scale = 1.0f;
	nextPieceText.color = glm::vec4(1.0f);
	scoreText.chaine = std::string("Score : ").append(std::to_string(score));
	scoreText.position = glm::vec2(10.0f, SCREEN_HEIGHT * 0.8f);
	scoreText.scale = 1.0f;
	scoreText.color = glm::vec4(1.0f);
	gameOverText.chaine = "GAME OVER";
	gameOverText.position = glm::vec2(SCREEN_WIDTH * 0.5f - textRenderer->getSize("GAME OVER").x * 0.5, SCREEN_HEIGHT * 0.5f);
	gameOverText.scale = 1.0f;
	gameOverText.color = glm::vec4(1.0f);
	levelText.chaine = std::string("Niveau : ").append(std::to_string(level));
	levelText.position = glm::vec2(10.0f, SCREEN_HEIGHT * 0.6f);
	levelText.scale = 1.0f;
	levelText.color = glm::vec4(1.0f);
	pauseText.chaine = "PAUSE";
	pauseText.position = glm::vec2(SCREEN_WIDTH * 0.5f - textRenderer->getSize("PAUSE").x * 0.5, SCREEN_HEIGHT * 0.5f);
	pauseText.scale = 1.0f;
	pauseText.color = glm::vec4(1.0f);

}
void Game::Update(float deltaTime) {
	switch (gameState) {
	case PLAYING:
		timer -= deltaTime;
		if (timer < 0.0f && !keys[GLFW_KEY_S]) {
			if (playerPiece.Down(board))
				NewPiece();

			timer = maxTimer - ((level - 1) * levelTimerReduction);
		}
		break;
	}
	
}
void Game::Render() {

	for (int i = 0; i < tileHeight * tileWidth; i++)
		if (blocks[i].used)
			blocks[i].Render(*spriteRenderer);
	nextPieceVisual.Draw(*spriteRenderer);
	nextPieceText.Draw(*textRenderer);
	scoreText.Draw(*textRenderer);
	levelText.Draw(*textRenderer);
	if(gameState == GAMEOVER)
		gameOverText.Draw(*textRenderer);
	if (gameState == PAUSE)
		pauseText.Draw(*textRenderer);
}
int Game::CheckRows() {
	bool clear;
	int rowCleared = 0;
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
			rowCleared++;
			i--; //permet de repasser sur la ligne qui vient d'être supprimé
		}
			
	}
	return rowCleared;
}
void Game::ClearRow(int row) {
	for (int i = 1; i < tileWidth - 1; i++) {
		board[i][row].GetBlock()->used = false;
		board[i][row].state = EMPTY;
		board[i][row].block = nullptr;
	}
	for (int i = row + 1; i < tileHeight - 4; i++) {
		for (int j = 1; j < tileWidth - 1; j++) {
			if (board[j][i].state == FULL) {
				board[j][i].GetBlock()->SetPos(board[j][i - 1]);
				board[j][i].state = EMPTY;
				board[j][i - 1].state = FULL;
				board[j][i].block = nullptr;
			}
		}
	}
}
void Game::UpdateScore(int rowNumber) {
	switch (rowNumber) {
	case 1:
		score += (baseRowPoint * level);
		break;
	case 2:
		score += (baseRowPoint * level * 2) * 2;
		break;
	case 3:
		score += (baseRowPoint * level * 3) * 3;
		break;
	case 4:
		score += (baseRowPoint * level * 4) * 5;
		break;
	}
	scoreText.chaine = std::string("Score : ").append(std::to_string(score));
}
void Game::UpdateLevel() {
	if (score >= levelUpTreshold) {
		level++;
		levelUpTreshold *= 2;
		levelText.chaine = std::string("Niveau : ").append(std::to_string(level));
	}
	
}
void Game::CheckGameOver() {
	for (int i = 1; i < tileWidth - 1; i++) {
		for (int j = tileHeight - 5; j < tileHeight; j++) {
			if (board[i][j].state == FULL)
				gameState = GAMEOVER;
		}
	}
}

void Game::Restart() {
	for (int i = 1; i < tileWidth - 1; i++) {
		for (int j = 1; j < tileHeight - 1; j++) {
			board[i][j].block = nullptr;
			board[i][j].state = EMPTY;
		}
	}
	for (int i = nombreBlockBordure; i < tileHeight * tileWidth; i++)
		blocks[i].used = false;

	score = 0;
	level = 1;
	levelUpTreshold = baseLevelUpTreshold;
	scoreText.chaine = std::string("Score : ").append(std::to_string(score));
	gameState = PLAYING;
	nextShape = (SHAPE)(rand() % 7);
	playerPiece.Spawn(blocks.get(), nombreBlockBordure, board, nextShape);
	nextShape = (SHAPE)(rand() % 7);
	SetNewPieceVisual();
}

void Game::ProcessInput(float deltaTime) {
	if (gameState == PLAYING) {
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
		if (keys[GLFW_KEY_P] && !lockKeys[GLFW_KEY_P]) {
			gameState = PAUSE;
			lockKeys[GLFW_KEY_P] = true;
		}
		else if (!keys[GLFW_KEY_P] && lockKeys[GLFW_KEY_P]) {
			lockKeys[GLFW_KEY_P] = false;
		}
		if (keys[GLFW_KEY_SPACE] && !lockKeys[GLFW_KEY_SPACE]) {
			playerPiece.SwapPiece(board, nextShape);
			SetNewPieceVisual();
			lockKeys[GLFW_KEY_SPACE] = true;
		}
		else if (!keys[GLFW_KEY_SPACE] && lockKeys[GLFW_KEY_SPACE]) {
			lockKeys[GLFW_KEY_SPACE] = false;
		}
	}
	else if (gameState == GAMEOVER) {
		if (keys[GLFW_KEY_R] && !lockKeys[GLFW_KEY_R]) {
			Restart();
			lockKeys[GLFW_KEY_Q] = true;
		}
		else if (!keys[GLFW_KEY_R] && lockKeys[GLFW_KEY_R]) {
			lockKeys[GLFW_KEY_Q] = false;
		}
	}
	else if (gameState == PAUSE) {
		if (keys[GLFW_KEY_P] && !lockKeys[GLFW_KEY_P]) {
			gameState = PLAYING;
			lockKeys[GLFW_KEY_P] = true;
		}
		else if (!keys[GLFW_KEY_P] && lockKeys[GLFW_KEY_P]) {
			lockKeys[GLFW_KEY_P] = false;
		}
	}
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
	UpdateScore(CheckRows());
	UpdateLevel();
	CheckGameOver();
	playerPiece.Spawn(blocks.get(), nombreBlockBordure, board,nextShape);
	nextShape = nextShape = (SHAPE)(rand() % 7);
	SetNewPieceVisual();
}

bool Game::IsOver() {
	return gameState == END;
}

void CheckIntegrity(Tile(&board)[tileWidth][tileHeight]) {
	for (int i = 0; i < tileWidth; i++) {
		for (int j = 0; j < tileHeight; j++) {
			if (board[i][j].state == FULL && board[i][j].block == nullptr)
				std::cout << "GROS PROBLEME x : " << i << " ; y : " << j << std::endl;
		}
	}
}