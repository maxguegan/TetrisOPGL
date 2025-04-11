#include "Game.h"

SpriteRenderer * spriteRenderer;

Game::Game(const float width, const float height): SCREEN_WIDTH(width), SCREEN_HEIGHT(height), score(0), nombreBlock(0), state(PLAYING) {
	for (int i = 0; i < 1024; i++) {
		keys[i] = false;
		lockKeys[i] = false;
	}
}

void Game::Init() {
	InitRessource();
	spriteRenderer = new SpriteRenderer(Ressource::GetShader("sprite_shader"));
	glm::mat4 projection = glm::ortho(0.0f, SCREEN_WIDTH, 0.0f, SCREEN_HEIGHT, -1.0f, 1.0f);
	Ressource::GetShader("sprite_shader").setMat4("projection", projection);
	InitMap();
}

void Game::InitMap() {
	const float offsetX = (SCREEN_WIDTH - tileWidth * tileSize) / 2.0f ;
	
	//positionne toute les cases de la grille dans la fenêtre 
	for (int i = 0; i < tileHeight; i++) {
		for (int j = 0; j < tileWidth; j++) {
			board[j][i].position = glm::vec2(offsetX + j * tileSize, i * tileSize);
			if ((i == 0 || j == 0 || j == tileWidth - 1) && i <= 21) {
				blocks[nombreBlock].Init(Ressource::GetTexture("block_limite"), tileSize, board[j][i]);
				nombreBlock++;
			}
				
		}
		
	}
	
}

void Game::InitRessource() {
	Ressource::LoadShader(std::filesystem::path{ "../shader/SpriteShader.vs" }.string().c_str(), NULL, std::filesystem::path{"../shader/SpriteShader.fs"}.string().c_str(), "sprite_shader");
	Ressource::LoadTexture(std::filesystem::path{ "../texture/block_limite.png" }.string().c_str(), false, "block_limite");


}


void Game::Render() {
	
	for(int i = 0; i < nombreBlock; i++)
		blocks[i].Render(*spriteRenderer);
}


bool Game::IsOver() {
	return state == OVER;
}