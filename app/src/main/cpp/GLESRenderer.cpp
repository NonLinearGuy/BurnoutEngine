//
// Created by Ankit Singh on 05-10-2018.
//

#include "GLESRenderer.hpp"
#include "android/log.h"
#include <GLES3/gl3.h>
#include<sstream>
#include<cstdio>
#include<ShaderProgram.hpp>
#include<TexturedPlane.hpp>
#include<glm/glm.hpp>
#include"Texture2D.h"
#include"SpriteRenderer.h"


#define LOG(msg) __android_log_print(100,"EGL Error",msg);

GLESRenderer::GLESRenderer(android_app* pState)
        :
       m_State(pState),
        m_Display(EGL_NO_DISPLAY),
        m_Context(EGL_NO_CONTEXT),
        m_Surface(EGL_NO_SURFACE)
{

}

GLESRenderer::~GLESRenderer()
{

}

bool GLESRenderer::OnInit()
{
    bool displayDone = InitDisplay();
    bool surfaceDone = InitSurface();
    bool contextDone = InitContext();

    if(displayDone  && surfaceDone && contextDone)
    {
        if (EGL_FALSE == eglMakeCurrent(m_Display,m_Surface, m_Surface,m_Context))
        {
            LOG("Renderer: eglMakeCurrent failed");
            return false;
        }

        glClearColor(0.0f,0.0f,0.0f,1.0f);
        SetState(EProcessState::RUNNING);

        SetupObjects();

        glEnable(GL_DEPTH_TEST);

        return true;
    }
    else
    return false;
}

void GLESRenderer::SetupObjects()
{
    TexturedPlane* plane = new TexturedPlane(glm::vec3(0.0f),glm::vec3(1.0f));
    plane->Init();
    mObjects.push_back(plane);

    glm::mat4 projection = glm::perspective(45.0f,m_Width/float(m_Height),0.1f,100.0f);
    for(auto object : mObjects)
    {
        object->GetShader().Use();
        object->GetShader().SetMat4("projection",projection);
    }

  //  AAssetDir* dir = AAssetManager_openDir(m_State->activity->assetManager,"");
    mTexture = new Texture2D("textures/tank.png");

    glm::mat4 orthProj = glm::ortho(0.0f,float(m_Width),float(m_Height),0.0f,0.0f,1.0f);
    mSprite = new SpriteRenderer();
    mSprite->Init();
    mSprite->GetShader().SetMat4("projection",orthProj);
}


void GLESRenderer::OnAbort()
{
    eglMakeCurrent(m_Display,EGL_NO_SURFACE,EGL_NO_SURFACE,EGL_NO_CONTEXT);
    eglDestroySurface(m_Display,m_Surface);
    eglDestroyContext(m_Display,m_Context);
    eglTerminate(m_Display);

    m_Display = EGL_NO_DISPLAY;
    m_Surface = EGL_NO_SURFACE;
    m_Context = EGL_NO_CONTEXT;

    for(auto object : mObjects)
        object->Destroy();
}

bool GLESRenderer::InitDisplay()
{
    m_Display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    if( EGL_FALSE == eglInitialize(m_Display,0,0))
    {
        LOG("failed to initialize egl");
        return false;
    }

    return true;
}

bool GLESRenderer::InitSurface()
{
    EGLint numConfigs;

    const EGLint attribs[] =
            {
                    EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
                    EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                    EGL_BLUE_SIZE, 8,
                    EGL_GREEN_SIZE, 8,
                    EGL_RED_SIZE, 8,
                    EGL_DEPTH_SIZE, 16,
                    EGL_NONE
            };

    eglChooseConfig(m_Display, attribs, &m_Config, 1, &numConfigs);


    EGLint attribList[] =
            {
                    EGL_RENDER_BUFFER, EGL_BACK_BUFFER,
                    EGL_NONE
            };

    m_Surface = eglCreateWindowSurface(m_Display,m_Config,m_State->window,attribList);


    if(EGL_NO_SURFACE == m_Surface)
    {
        LOG("failed to create surface")
        return false;
    }

    eglQuerySurface(m_Display,m_Surface,EGL_WIDTH,&m_Width);
    eglQuerySurface(m_Display,m_Surface,EGL_HEIGHT,&m_Height);

    glViewport(0,0,m_Width,m_Height);

    return true;
}

bool GLESRenderer::InitContext()
{
    EGLint attribList[] = {EGL_CONTEXT_CLIENT_VERSION,3,EGL_NONE};

    m_Context = eglCreateContext(m_Display,m_Config,NULL,attribList);
    if(EGL_NO_CONTEXT == m_Context)
    {
        LOG("failed to create egl context");
        return false;
    }

    return true;
}

void GLESRenderer::Update(float DeltaTime)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(auto object : mObjects)
        object->Tick();

    for(auto object : mObjects)
        object->Render();

    mSprite->DrawImage(*mTexture,glm::vec2(m_Width/2.0f,m_Height/2.0f),glm::vec2(100.0f),glm::vec4(1.0f),0.0f);

    eglSwapBuffers(m_Display,m_Surface);
}
