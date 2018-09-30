//
// Created by czh on 18-9-21.
//

#ifndef OPENGL_ES_BALL_OBJECT_H
#define OPENGL_ES_BALL_OBJECT_H

#include <GLES3/gl3.h>
#include "game_object.h"

class BallObject : public GameObject {
public:
    GLfloat radius;
    GLboolean stuck;

    BallObject();

    BallObject(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture2D texture2D);

    glm::vec2 move(GLfloat refreshTime, GLuint window_width);

    void reset(glm::vec2 position, glm::vec2 velocity);
};


#endif //OPENGL_ES_BALL_OBJECT_H
