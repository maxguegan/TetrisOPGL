#pragma once

#include <string.h>
#include <glm/glm.hpp>
#include "TextRenderer.h"


class UIText {
public:
	std::string chaine;

	glm::vec2 position;
	glm::vec4 color;

	float scale;

public:
	UIText();
	UIText(std::string chaine, glm::vec2 position, float scale, glm::vec4 color);
	void Draw(TextRenderer& textRenderer);
};
