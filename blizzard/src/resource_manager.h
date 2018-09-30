//
// Created by czh on 18-9-10.
//

#ifndef OPENGL_PRO_RESOURCE_MANAGER_H
#define OPENGL_PRO_RESOURCE_MANAGER_H

#include <iostream>
#include <map>
#include <GLES3/gl3.h>
#include <stb_image/stb_image.h>
#include <opencv2/opencv.hpp>
#include "shader.h"
#include "texture.h"

class ResourceManager {
public:

    static std::map<std::string, Shader> shaders;

    static std::map<std::string, Texture2D> textures;

    static Shader
    loadShader(std::string name, const GLchar *vShader, const GLchar *fShader, const GLchar *gShader = nullptr);

    static Shader getShader(std::string name);

    static Texture2D loadTexture2D(std::string name, const GLchar *file, GLboolean alpha = false);

    static Texture2D getTexture2D(std::string name);

    static void clear();

private:
    ResourceManager() {}

    static Texture2D loadTexture2DFromfile(const GLchar *file, GLboolean alpha);

};


#endif //OPENGL_PRO_RESOURCE_MANAGER_H
