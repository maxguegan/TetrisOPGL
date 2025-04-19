#include "UIText.h"

UIText::UIText():chaine(""), position(glm::vec2(0.0f)), scale(0.0f), color(glm::vec4(0.0f)){}

UIText::UIText(std::string chaine, glm::vec2 position, float scale, glm::vec4 color)
	:chaine(chaine), position(position), scale(scale), color(color) {}


void UIText::Draw(TextRenderer& textRenderer) {
	textRenderer.DrawText(chaine, position.x, position.y, scale, color);
}