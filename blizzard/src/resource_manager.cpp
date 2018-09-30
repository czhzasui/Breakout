//
// Created by czh on 18-9-10.
//

#include "resource_manager.h"

std::map<std::string, Texture2D>    ResourceManager::textures;
std::map<std::string, Shader>       ResourceManager::shaders;

void ResourceManager::clear() {

}

Shader
ResourceManager::loadShader(std::string name, const GLchar *vShader, const GLchar *fShader, const GLchar *gShader) {
    Shader shader;
    shader.compile(vShader, fShader, gShader);
    shaders[name] = shader;
}

Shader ResourceManager::getShader(std::string name) {
    return shaders[name];
}

Texture2D ResourceManager::loadTexture2DFromfile(const GLchar *file, GLboolean alpha) {
    Texture2D texture;
#ifdef LOAD_TEXTURE_CV
    if (alpha) {
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format = GL_BGRA;
    } else {
        texture.Internal_Format = GL_RGB;
        texture.Image_Format = GL_BGR;
    }
    cv::Mat image = cv::imread(file, CV_LOAD_IMAGE_UNCHANGED);
    texture.generate(image.size().width, image.size().height, image.data);
#else
    if (alpha) {
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format = GL_RGBA;
    } else {
        texture.Internal_Format = GL_RGB;
        texture.Image_Format = GL_RGB;
    }
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(false);
    unsigned char *image = stbi_load(file, &width, &height, &nrChannels, 0);
    if (image == NULL) {
        std::cout << "loadTexture2D Error" << std::endl;
    }
    texture.generate(width, height, image);
    stbi_image_free(image);
#endif

#ifdef SML
    #ifdef LOAD_TEXTURE_CV
    std::cout << "#loadTexture2D \"" << file << "\" " << image.size().width << "*" << image.size().height;
    if (image.channels() == 4) {
        std::cout << " size:RGBA";
    } else if (image.channels() == 3) {
        std::cout << " size:RGB";
    }
    #else
    std::cout << "#loadTexture2D \"" << file << "\" " << width << "*" << height;
    if (nrChannels == 4) {
        std::cout << " size:RGBA";
    } else if (nrChannels == 3) {
        std::cout << " size:RGB";
    }
    #endif
#endif
    return texture;
}

Texture2D ResourceManager::loadTexture2D(std::string name, const GLchar *file, GLboolean alpha) {
    textures[name] = loadTexture2DFromfile(file, alpha);
#ifdef SML
    std::cout << " name:" << name << std::endl;
#endif
}

Texture2D ResourceManager::getTexture2D(std::string name) {
    return textures[name];
}
