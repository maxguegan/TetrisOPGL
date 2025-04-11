#pragma once
#include <filesystem>
#include <glm/geometric.hpp>
#include "Ressource.h"
#include "Block.h"


enum GAMESTATE
{
	PLAYING,
	OVER
};
const float maxTimer = 1.5f;
const int tileHeight = 25; // taille de 20 plus la bordures inférieures et la limite supérieur (20 + 1 + 4)
const int tileWidth = 12; // taille de 10 plus les bordures droites et gauche
class Game {
public:
	
	bool keys[1024];
	bool lockKeys[1024];
	const float SCREEN_WIDTH, SCREEN_HEIGHT;
	const float tileSize = 20.0f;

public:
	Game(const float width, const float height);
	void Init();
	void Render();
	void Update(float deltaTime);
	void ProcessInput();
	bool IsOver();
private:

	int score, nombreBlock;
	float timer = maxTimer;

	Block blocks[tileWidth * tileHeight];
	Tile board[tileWidth][tileHeight];
	GAMESTATE state;
	
private:
	void InitMap();
	void InitRessource();
	void Restart();

};