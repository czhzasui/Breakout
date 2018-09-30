//
// Created by czh on 18-9-10.
//

#ifndef OPENGL_PRO_SHADER_H
#define OPENGL_PRO_SHADER_H

#include <iostream>
#include <GLES3/gl3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "dconfig.h"

class Shader {
public:

    Shader() {};

    int ID;

    Shader &use();

    void compile(const GLchar *vShaderSource, const GLchar *fShaderSource, const GLchar *gShaderSource);

    void setInteger(const GLchar *name, GLint value, GLboolean useShader = true);

    void setVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader = true);

    void setVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader = true);

    void setMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = true);

private:
    void checkCompileErrors(GLuint object, std::string type);
};


#endif //OPENGL_PRO_SHADER_H
