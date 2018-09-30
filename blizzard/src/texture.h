//
// Created by czh on 18-9-10.
//

#ifndef OPENGL_PRO_TEXTURE_H
#define OPENGL_PRO_TEXTURE_H

#include <GLES3/gl3.h>
#include "dconfig.h"

class Texture2D {
public:
    GLuint ID;
    GLuint width, height;
    GLuint Internal_Format;
    GLuint Image_Format;

    GLuint Wrap_S;
    GLuint Wrap_T;
    GLuint Filter_Min;
    GLuint Filter_Max;

    Texture2D();

    void generate(GLuint width, GLuint height, unsigned char* data);

    void bind() const;
};


#endif //OPENGL_PRO_TEXTURE_H
