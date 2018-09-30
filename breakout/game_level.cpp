//
// Created by czh on 18-9-18.
//

#include "game_level.h"

GameLevel::GameLevel() {

}

void GameLevel::load(const GLchar *file, float levelWidth, float levelHeight) {

    this->bricks.clear();
    GLuint tileCode;
    std::string line;
    std::ifstream fstream(file);
    std::vector<std::vector<GLuint>> tileData;
    if (fstream) {
        while (std::getline(fstream, line)) // Read each line from level file
        {
            std::istringstream sstream(line);
            std::vector<GLuint> row;
            while (sstream >> tileCode)
                row.push_back(tileCode);
            tileData.push_back(row);
        }
        if (tileData.size() > 0)
            this->init(tileData, levelWidth, levelHeight);
    }
}

void GameLevel::draw(SpriteRenderer *spriteRenderer) {
    for (auto &gameObject : this->bricks) {
        if (!gameObject.destroyed) {
            gameObject.draw(spriteRenderer);
        }
    }
}

GLboolean GameLevel::isCompleted() {
    for (GameObject &tile : this->bricks)
        if (!tile.isSolid && !tile.destroyed)
            return GL_FALSE;
    return GL_TRUE;
}

void GameLevel::init(std::vector<std::vector<GLuint>> tileData, float levelWidth, float levelHeight) {
    GLuint height = tileData.size();
    GLuint width = tileData[0].size();
    GLfloat block_width = levelWidth / (float)width;
    GLfloat block_height = levelHeight / (float)height;

    for (GLuint y = 0; y < height; ++y) {
        for (GLuint x = 0; x < width; ++x) {
            if (tileData[y][x] == 1)        //Solid
            {
                glm::vec2 pos(block_width * x, block_height * y);
                glm::vec2 size(block_width, block_height);
                GameObject gameObject(pos, size, ResourceManager::getTexture2D("block_solid"), glm::vec3(0.8f, 0.8f, 0.7f));
                gameObject.isSolid = GL_TRUE;
                this->bricks.push_back(gameObject);
            } else if (tileData[y][x] > 1)  //Non-solid
            {
                glm::vec3 color = glm::vec3(1.0f);
                if (tileData[y][x] == 2)
                    color = glm::vec3(0.2f, 0.6f, 1.0f);//blue
                else if (tileData[y][x] == 3)
                    color = glm::vec3(0.0f, 0.7f, 0.0f);//green
                else if (tileData[y][x] == 4)
                    color = glm::vec3(0.8f, 0.8f, 0.4f);//yellow
                else if (tileData[y][x] == 5)
                    color = glm::vec3(1.0f, 0.5f, 0.0f);//orange

                glm::vec2 pos(block_width * x, block_height * y);
                glm::vec2 size(block_width, block_height);
                this->bricks.push_back(GameObject(pos, size, ResourceManager::getTexture2D("block"), color));
            }
        }
    }
}
