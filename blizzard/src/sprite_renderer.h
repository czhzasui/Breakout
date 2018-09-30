//
// Created by czh on 18-9-10.
//

#ifndef OPENGL_PRO_SPRITE_H
#define OPENGL_PRO_SPRITE_H

#include <GLES3/gl3.h>
#include "shader.h"
#include "texture.h"
#include "dconfig.h"

class SpriteRenderer {
public:
    SpriteRenderer(Shader shader);

    ~SpriteRenderer();

    void drawSprite(Texture2D texture, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f,
                    glm::vec3 color = glm::vec3(1.0f));

private:
    Shader shader;
    GLuint VAO;

    void init();

    GLfloat vertices[24] = {
            // Pos      // Tex
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,

            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f
    };
};


#endif //OPENGL_PRO_SPRITE_H
