//
// Created by czh on 18-9-18.
//

#ifndef OPENGL_ES_GAME_OBJECT_H
#define OPENGL_ES_GAME_OBJECT_H

#include <GLES3/gl3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "blizzard/src/texture.h"
#include "blizzard/src/sprite_renderer.h"

class GameObject {
public:
    glm::vec2   position, size, velocity;
    glm::vec3   color;
    GLfloat     rotation;
    GLboolean   isSolid;
    GLboolean   destroyed;
    Texture2D   texture2D;

    GameObject();

    GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

    virtual void draw(SpriteRenderer *spriteRenderer);
};


#endif //OPENGL_ES_GAME_OBJECT_H
