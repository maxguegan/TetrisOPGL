#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Texture.h"
#include "SpriteRenderer.h"
#include "Tile.h"
class GameObject
{
public:
	glm::vec2 position;
	glm::vec2 size;

	float rotation;

	glm::vec4 color;

	Texture * sprite;


	GameObject(glm::vec2 pos = glm::vec2(0.0f), glm::vec2 size = glm::vec2(0.0f), glm::vec4 color = glm::vec4(1.0f), float rotation = 0.0f);
	void SetTexture(Texture* tex);
	virtual void draw(SpriteRenderer & renderer);

	~GameObject();

};

