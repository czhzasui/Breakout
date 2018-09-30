//
// Created by czh on 18-9-18.
//

#include "game.h"

const glm::vec2 PADDLE_SIZE(200, 20);
const GLfloat PADDLE_VELOCITY = 2.0f;
const glm::vec2 INITIAL_BALL_VELOCITY(0.07f, -0.245f);//y = -3.5f * x
const GLfloat BALL_RADIUS = 12.5f;

SpriteRenderer *spriteRender;
GameObject *paddle;
BallObject *ball;

Game::Game(GLuint width, GLuint height)
        : state(GAME_ACTIVE), keys(), width(width), height(height) {

}

Game::~Game() {
    delete spriteRender;
}

void Game::init() {
    system("killall -9 hmi");
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    this->state = GAME_ACTIVE;

    ResourceManager::loadShader("sprite", defaultVshaderStr, defaultFshaderStr);

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::ortho(0.0f, static_cast<GLfloat>(this->width), static_cast<GLfloat>(this->height), 0.0f, -1.0f,
                            1.0f);
    ResourceManager::getShader("sprite").setInteger("image", 0);
    ResourceManager::getShader("sprite").setMatrix4("projection", projection);
    ResourceManager::loadTexture2D("background", "/data/res/textures/background.jpg", false);
    ResourceManager::loadTexture2D("block", "/data/res/textures/block.png", false);
    ResourceManager::loadTexture2D("block_solid", "/data/res/textures/block_solid.png", false);
    ResourceManager::loadTexture2D("paddle", "/data/res/textures/paddle.png", true);
    ResourceManager::loadTexture2D("ball", "/data/res/textures/facebuke.png", true);

    ResourceManager::getShader("sprite").setVector4f("location", glm::vec4(1.0f, 1.0f, 0.0f, 0.0f));

    GameLevel levelOne;
    levelOne.load("/data/res/levels/one.lvl", this->width, this->height * 0.5);
    GameLevel levelTwo;
    levelTwo.load("/data/res/levels/one.lvl", this->width, this->height * 0.5);

    this->levels.push_back(levelOne);
    this->levels.push_back(levelTwo);
    this->level = 1;

    spriteRender = new SpriteRenderer(ResourceManager::getShader("sprite"));

    glm::vec2 paddlePos = glm::vec2(
            (this->width - PADDLE_SIZE.x) / 2,
            this->height - PADDLE_SIZE.y
    );
    paddle = new GameObject(paddlePos, PADDLE_SIZE, ResourceManager::getTexture2D("paddle"));
    glm::vec2 ballPos = paddlePos + glm::vec2(PADDLE_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2);
    ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY,
                          ResourceManager::getTexture2D("ball"));
}

void Game::destory() {
    system("/home/root/shell/hmi -platform eglfs &");
    QCoreApplication::exit(0);
}

void Game::processInput(float refreshTime, Command *command) {
    if (this->state == GAME_ACTIVE) {
        GLfloat dx = PADDLE_VELOCITY * refreshTime;
        if (Rotate_Left == command->rotate) {
            if (paddle->position.x >= 0) {
                paddle->position.x -= dx;
            }
            if (ball->stuck) {
                ball->position.x -= dx;
            }
        }
        if (Rotate_Right == command->rotate) {
            if (paddle->position.x <= this->width - paddle->size.x) {
                paddle->position.x += dx;
            }
            if (ball->stuck) {
                ball->position.x += dx;
            }
        }
        command->rotate = Rotate_Defalt;

        if (Key_Confirm == command->key) {
            ball->stuck = false;
        }
        if (Key_Homepage == command->key) {
            this->state = GAME_QUIT;
        }
        command->key = Key_Defalt;
    }
}

void Game::render() {
    if (this->state == GAME_ACTIVE) {
        spriteRender->drawSprite(ResourceManager::getTexture2D("background"), glm::vec2(0, 0),
                                 glm::vec2(this->width, this->height), 0.0f);
        this->levels[this->level].draw(spriteRender);
        paddle->draw(spriteRender);
        ball->draw(spriteRender);
    }
}

void Game::update(float refreshTime) {
    ball->move(refreshTime, this->width);

    this->doCollisions();

    if (ball->position.y >= this->height) {
        this->resetLevel();
        this->resetPlayer();
    }
}

void Game::resetLevel() {
    if (this->level == 0)
        this->levels[0].load("/data/res/levels/one.lvl", this->width, this->height * 0.5f);
    else if (this->level == 1)
        this->levels[1].load("/data/res/levels/one.lvl", this->width, this->height * 0.5f);
}

void Game::resetPlayer() {
    paddle->size = PADDLE_SIZE;
    paddle->position = glm::vec2(this->width / 2 - PADDLE_SIZE.x / 2, this->height - PADDLE_SIZE.y);
    ball->reset(paddle->position + glm::vec2(PADDLE_SIZE.x / 2 - BALL_RADIUS, -(BALL_RADIUS * 2)),
                INITIAL_BALL_VELOCITY);
}

void Game::doCollisions() {
    for (GameObject &brick : this->levels[this->level].bricks) {
        if (!brick.destroyed) {
            Collision collision = checkCollision(*ball, brick);
            if (std::get<0>(collision)) {
                if (!brick.isSolid)
                    brick.destroyed = GL_TRUE;
                Direction dir = std::get<1>(collision);
                glm::vec2 diff_vector = std::get<2>(collision);
                if (dir == LEFT || dir == RIGHT) {
                    ball->velocity.x = -ball->velocity.x;
                    GLfloat penetration = ball->radius - std::abs(diff_vector.x);
                    if (dir == LEFT)
                        ball->position.x += penetration; // Move ball to right
                    else
                        ball->position.x -= penetration; // Move ball to left;
                } else {
                    ball->velocity.y = -ball->velocity.y;
                    GLfloat penetration = ball->radius - std::abs(diff_vector.y);
                    if (dir == UP)
                        ball->position.y -= penetration; // Move ball back up
                    else
                        ball->position.y += penetration; // Move ball back down
                }
            }
        }
    }
    Collision result = checkCollision(*ball, *paddle);
    if (!ball->stuck && std::get<0>(result)) {
        GLfloat centerPaddle = paddle->position.x + paddle->size.x / 2;
        GLfloat distance = (ball->position.x + ball->radius) - centerPaddle;
        GLfloat percentage = distance / (paddle->size.x / 2);
        // Then move accordingly
        GLfloat strength = 2.0f;
        glm::vec2 oldVelocity = ball->velocity;
        ball->velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
        ball->velocity = glm::normalize(ball->velocity) * glm::length(oldVelocity);
        ball->velocity.y = -1 * std::abs(ball->velocity.y);
    }
}

Direction VectorDirection(glm::vec2 target) {
    glm::vec2 compass[] = {
            glm::vec2(0.0f, 1.0f),    // up
            glm::vec2(1.0f, 0.0f),    // right
            glm::vec2(0.0f, -1.0f),    // down
            glm::vec2(-1.0f, 0.0f)    // left
    };
    GLfloat max = 0.0f;
    GLuint best_match = -1;
    for (GLuint i = 0; i < 4; i++) {
        GLfloat dot_product = glm::dot(glm::normalize(target), compass[i]);
        if (dot_product > max) {
            max = dot_product;
            best_match = i;
        }
    }
    return (Direction) best_match;
}

Collision Game::checkCollision(BallObject &ball, GameObject &gameObject) {
    glm::vec2 ballCenter(ball.position + ball.radius);
    glm::vec2 brick_half_extents(gameObject.size.x / 2, gameObject.size.y / 2);
    glm::vec2 brick_center(gameObject.position.x + brick_half_extents.x, gameObject.position.y + brick_half_extents.y);
    glm::vec2 distance = ballCenter - brick_center;
    glm::vec2 clamped = glm::clamp(distance, -brick_half_extents, brick_half_extents);
    glm::vec2 closestPoint = brick_center + clamped;
    distance = closestPoint - ballCenter;
    if (glm::length(distance) < ball.radius)
        return std::make_tuple(GL_TRUE, VectorDirection(distance), distance);
    else
        return std::make_tuple(GL_FALSE, UP, glm::vec2(0, 0));
}
