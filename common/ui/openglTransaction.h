//
// Created by czh on 18-8-27.
//

#ifndef J59R_SIM_OPENGLTRANSACTION_H
#define J59R_SIM_OPENGLTRANSACTION_H
#include <EGL/egl.h>
#include <GLES/gl.h>
#include <GLES2/gl2.h>
#include <stdio.h>

bool opengl_init(int fb_num);

void opengl_destroy();

bool CreateOpenglShareContext();

bool DestoryOpenGLShareContext();

void postDisplay();

#endif //J59R_SIM_OPENGLTRANSACTION_H
