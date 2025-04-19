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


	int score, niveau, nombreBlockBordure;
	float timer = maxTimer;
    float inputTimer = maxInputTimer;


	PlayerPiece playerPiece;
	Block * blocks = new Block[tileWidth * tileHeight];
	Tile board[tileWidth][tileHeight];
	GAMESTATE gameState;
	SHAPE nextShape;

	GameObject nextPieceVisual;
	UIText nextPieceText, scoreText, gameOverText;

	std::unique_ptr<SpriteRenderer> spriteRenderer;
	std::unique_ptr<TextRenderer> textRenderer;

private:
	void InitMap();
	void InitRessource();
	void CheckRows();
	void ClearRow(int row);
	void CheckGameOver();
	void NewPiece();
	void SetNewPieceVisual();
	void UpdateScore(int rowNumber);
	void Restart();

};