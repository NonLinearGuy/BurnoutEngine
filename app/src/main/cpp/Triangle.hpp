//
// Created by Ankit Singh on 27-10-2018.
//

#ifndef BURNOUTENGINE_TRIANGLE_HPP
#define BURNOUTENGINE_TRIANGLE_HPP

#include"android_native_app_glue.h"
#include"EGL/egl.h"
#define LOG(msg) __android_log_print(100,"EGL Error",msg);

class Triangle {
private:
    android_app* mApp;
   public:

   Triangle(android_app* state);
   void SetupGLES();
    void SetupVertices();
    void SetupShaders();
    void Tick();

private:
    EGLContext  context;
    EGLSurface  surface;
    EGLDisplay  display;
    EGLConfig   config;
    EGLint      width;
    EGLint      height;
};


#endif //BURNOUTENGINE_TRIANGLE_HPP
