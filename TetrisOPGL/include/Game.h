#pragma once
#include <filesystem>
#include <glm/geometric.hpp>
#include "Ressource.h"
#include "Block.h"
#include "Settings.h"
#include "PlayerPiece.h"
#include "TextRenderer.h"
#include "UIText.h"

enum GAMESTATE
{
	PLAYING,
	GAMEOVER,
	END
};

class Game {
public:
	
	bool keys[1024];
	bool lockKeys[1024];
	const float SCREEN_WIDTH, SCREEN_HEIGHT;


public:
	Game(const float width, const float height);
	void Init();
	void Render();
	void Update(float deltaTime);
	void ProcessInput(float deltaTime);
	bool IsOver();
private:


	int score, level, nombreBlockBordure;
	int levelUpTreshold = baseLevelUpTreshold;
	float timer = maxTimer;
    float inputTimer = maxInputTimer;


	PlayerPiece playerPiece;
	std::unique_ptr<Block[]> blocks = std::make_unique<Block[]>(tileHeight * tileWidth);
	Tile board[tileWidth][tileHeight];
	GAMESTATE gameState;
	SHAPE nextShape;

	GameObject nextPieceVisual;
	UIText nextPieceText, scoreText, gameOverText, levelText;

	std::unique_ptr<SpriteRenderer> spriteRenderer;
	std::unique_ptr<TextRenderer> textRenderer;

private:
	void InitMap();
	void InitRessource();
	void InitUI();
	int CheckRows();
	void ClearRow(int row);
	void CheckGameOver();
	void NewPiece();
	void SetNewPieceVisual();
	void UpdateScore(int rowNumber);
	void UpdateLevel();
	void Restart();

};