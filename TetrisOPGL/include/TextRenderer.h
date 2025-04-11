#pragma once
#include <iostream>
#include <string>
#include <map>
#include <ft2build.h>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include FT_FREETYPE_H
#include "Shader.h"
struct Character
{
	unsigned int textID;
	glm::vec2 size;
	glm::vec2 bearing;
	unsigned int advance;
};

class TextRenderer
{
public:
	std::map<char, Character> characters;
	TextRenderer(const char * fonts);
	void DrawText(std::string chaine, float x, float y, float scale, glm::vec3 color, Shader& shader);
private:
	unsigned int vao, vbo;
	void setupBuffer();
	glm::mat4 orthoProjection;
};

