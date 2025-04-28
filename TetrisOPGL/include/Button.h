#pragma once

#include "GameObject.h"
#include "TextRenderer.h"
#include "UIText.h"
#include <glm/glm.hpp>
#include <string>

class Button {

public:
	GameObject backGround;
	glm::vec4 backGroundColor, textColor;

public:

	Button(std::string text = std::string(""), glm::vec2 position = glm::vec2(0.0f), glm::vec2 size = glm::vec2(0.0f),
		glm::vec4 backGroundColor = glm::vec4(1.0f), glm::vec4 textColor = glm::vec4(1.0f));
	void SetText(std::string, TextRenderer & renderer);
	void SetPosition(glm::vec2 position);
	void SetSize(glm::vec2 size);
private:
	UIText buttonText;
	glm::vec2 position;
	glm::vec2 size;
};