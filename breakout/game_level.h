//
// Created by czh on 18-9-18.
//

#ifndef OPENGL_ES_GAME_LEVEL_H
#define OPENGL_ES_GAME_LEVEL_H

#include <GLES3/gl3.h>
#include <fstream>
#include <sstream>
#include <vector>
#include "sprite_renderer.h"
#include "game_object.h"
#include "resource_manager.h"

class GameLevel {
public:
    std::vector<GameObject> bricks;

    GameLevel();

    void load(const GLchar *file, float levelWidth, float levelHeight);

    void draw(SpriteRenderer *spriteRenderer);

    GLboolean isCompleted();

private:
    void init(std::vector<std::vector<GLuint>> tileData, float levelWidth, float levelHeight);
};


#endif //OPENGL_ES_GAME_LEVEL_H
