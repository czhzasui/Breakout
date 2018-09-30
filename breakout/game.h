//
// Created by czh on 18-9-18.
//

#ifndef OPENGL_ES_GAME_H
#define OPENGL_ES_GAME_H

#include <QObject>
#include <QCoreApplication>
#include <QtDBus/QDBusConnection>
#include <QDebug>
#include <thread>
#include <unistd.h>
#include <opencv2/opencv.hpp>
#include <GLES3/gl3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <unistd.h>
#include "game.h"
#include "ui/openglTransaction.h"
#include "dconfig.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "game_level.h"
#include "command.h"
#include "ball_object.h"

enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN,
    GAME_QUIT
};

enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

typedef std::tuple<GLboolean, Direction, glm::vec2> Collision;

class Game {

public:
    GameState state;
    float width, height;
    std::vector<GameLevel> levels;
    GLuint level;
    GLboolean keys[1024];

    Game(GLuint width, GLuint height);

    ~Game();

    void init();

    void destory();

    void processInput(float refreshTime, Command *command);

    void render();

    void update(GLfloat refreshTime);

    void resetLevel();

    void resetPlayer();

    void doCollisions();

    Collision checkCollision(BallObject &one, GameObject &two);

    const char *defaultVshaderStr =
            "#version 300 es                                    \n"
            "layout (location = 0) in vec4 vertex;              \n"
            "out vec2 TexCoords;                                \n"
            "uniform mat4 model;                                \n"
            "uniform mat4 projection;                           \n"
            "uniform vec4 location;                             \n"
            "void main()                                        \n"
            "{                                                  \n"
            "   TexCoords.x = vertex.z * location.x + location.z;\n"
            "   TexCoords.y = vertex.w * location.y + location.w;\n"
            "   gl_Position = projection * model * vec4(vertex.xy, 0.0f, 1.0f);\n"
            "}                                                  \n";

    const char *defaultFshaderStr =
            "#version 300 es                                    \n"
            "precision mediump float;                           \n"
            "in vec2 TexCoords;                                 \n"
            "out vec4 color;                                    \n"
            "uniform sampler2D image;                           \n"
            "uniform vec3 spriteColor;                          \n"
            "void main()                                        \n"
            "{                                                  \n"
            "   color = vec4(spriteColor, 1.0) * texture(image, TexCoords);\n"
            "}                                                  \n";
    
private:
};


#endif //OPENGL_ES_GAME_H
