//
// Created by czh on 18-8-27.
//

#include "openglTransaction.h"

EGLDisplay eglDisplay;
EGLContext context, context1;
EGLSurface eglSurface;
NativeDisplayType display;
NativeWindowType window;

bool createWindow(int fb_num) {

    // initialize opengl and egl
    const EGLint attribs[] =
            {
                    EGL_RED_SIZE, 8,
                    EGL_GREEN_SIZE, 8,
                    EGL_BLUE_SIZE, 8,
                    EGL_ALPHA_SIZE, 8,      //important for alpha blending with camera image
//        EGL_SURFACE_TYPE,EGL_WINDOW_BIT,
                    EGL_NONE
            };

    EGLint ctxAttribs[] =
            {
                    EGL_CONTEXT_CLIENT_VERSION, 2,
                    EGL_NONE
            };

    EGLint w, h, dummy;
    EGLint numConfigs;
    EGLConfig config;
    // EGLContext context;

    display = fbGetDisplayByIndex(fb_num);
    if (display == NULL) {
        printf("can not getDisplayByIndex");
        return false;
    }

    fbGetDisplayGeometry(display, &w, &h);

    window = fbCreateWindow(display, 0, 0, w, h);
    if (window == NULL) {
        printf("fbCreateWindow failed\n");
    }
    eglDisplay = eglGetDisplay(display);
    if (eglDisplay == EGL_NO_DISPLAY) {
        printf("EGL_NO_DISPLAY\n");
        return false;
    }
    if (!eglInitialize(eglDisplay, 0, 0)) {
        printf("eglInitialize failed\n");
        return false;
    }

    if (!eglChooseConfig(eglDisplay, attribs, &config, 1, &numConfigs)) {
        printf("eglChooseConfig failed\n");
        return false;
    }
    eglSurface = eglCreateWindowSurface(eglDisplay, config, window, NULL);
    if (eglSurface == EGL_NO_SURFACE) {
        printf("eglCreateWindowSurface failed\n");
        return false;
    }
    context = eglCreateContext(eglDisplay, config, NULL, ctxAttribs);
    context1 = eglCreateContext(eglDisplay, config, context, ctxAttribs);
    eglQuerySurface(eglDisplay, eglSurface, EGL_WIDTH, &w);
    eglQuerySurface(eglDisplay, eglSurface, EGL_HEIGHT, &h);

    if (eglMakeCurrent(eglDisplay, eglSurface, eglSurface, context) == EGL_FALSE)
        return false;
    // Set the viewport
    glViewport(0, 0, w, h);
    return true;
}

bool opengl_init(int fb_num) {
    if (!createWindow(fb_num)) {
        return false;
    }
    return true;
}

bool CreateOpenglShareContext() {
    if (eglMakeCurrent(eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, context1) == EGL_FALSE) {
        printf("eglMakeCurrent fail");
        return false;

    }
    return true;
}

bool DestoryOpenGLShareContext() {
    eglMakeCurrent(eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    return true;
}

void postDisplay() {
    eglSwapBuffers(eglDisplay, eglSurface);
    glClear(GL_COLOR_BUFFER_BIT);
}

void opengl_destroy(){
    eglMakeCurrent(eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglDestroyContext(eglDisplay, context);
    eglDestroyContext(eglDisplay, context1);
    eglDestroySurface(eglDisplay, eglSurface);
    eglTerminate(eglDisplay);
    eglReleaseThread();
}