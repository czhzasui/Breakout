//
// Created by czh on 18-9-18.
//

#include "game_object.h"

GameObject::GameObject() : position(0.0f, 0.0f), size(1.0f, 1.0f), velocity(0.0f), color(1.0f), rotation(0.0f), texture2D(),
                           isSolid(false), destroyed(false) {

}

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D texture2D, glm::vec3 color, glm::vec2 velocity)
        : position(pos), size(size), velocity(velocity), color(color), rotation(0.0f), texture2D(texture2D),
          isSolid(false), destroyed(false) {

}

void GameObject::draw(SpriteRenderer *spriteRenderer) {
    spriteRenderer->drawSprite(this->texture2D, this->position, this->size, this->rotation, this->color);
}
