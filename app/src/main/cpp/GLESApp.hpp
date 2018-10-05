//
// Created by Ankit Singh on 05-10-2018.
//

#ifndef BURNOUTENGINE_GLESAPP_HPP
#define BURNOUTENGINE_GLESAPP_HPP

#include"Application.hpp"

#include<EGL/egl.h>
#include<GLES3/gl3.h>


class GLESApp : public Application
{
public:

    GLESApp(android_app* p_State);
    ~GLESApp();
    virtual bool Initialize()override;
    virtual void Run()override;

private:

    EGLDisplay m_Display;
    EGLContext m_Context;
    EGLSurface m_Surface;
    int m_Width;
    int m_Height;

    android_app* m_State;

};


#endif //BURNOUTENGINE_GLESAPP_HPP
