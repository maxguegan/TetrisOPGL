#include "GameObject.h"


GameObject::GameObject(glm::vec2 position, glm::vec2 size,  glm::vec4 color,  float rotation): position(position), size(size), rotation(rotation), color(color)
{

}
void GameObject::SetTexture(Texture* tex) {
	sprite = tex;
}
void GameObject::draw(SpriteRenderer & renderer) {
	if (sprite == NULL) {
		std::cout << "Tentative de render un objet sans texture" << std::endl;
	}else
		renderer.Render(*(this->sprite), this->position, this->size, this->rotation, this->color);
}

GameObject::~GameObject(){}