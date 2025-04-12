#pragma once
#include <filesystem>
#include <glm/geometric.hpp>
#include "Ressource.h"
#include "Block.h"
#include "Settings.h"
#include "PlayerPiece.h"

enum GAMESTATE
{
	PLAYING,
	OVER
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
	void ProcessInput();
	bool IsOver();
private:

	int score, nombreBlock, nombreBlockBordure;
	float timer = maxTimer;

	PlayerPiece playerPiece;
	Block blocks[tileWidth * tileHeight];
	Tile board[tileWidth][tileHeight];
	GAMESTATE state;

	SpriteRenderer spriteRenderer;
	
private:
	void InitMap();
	void InitRessource();
	void Restart();

};