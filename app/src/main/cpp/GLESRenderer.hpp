//
// Created by Ankit Singh on 05-10-2018.
//

#ifndef BURNOUTENGINE_GLESRenderer_HPP
#define BURNOUTENGINE_GLESRenderer_HPP

#include"android_native_app_glue.h"
#include"IProcess.hpp"

#include<EGL/egl.h>
#include<GLES3/gl3.h>
#include<ShaderProgram.hpp>
#include<vector>
#include<map>


class GLESRenderer : public IProcess
{
public:

    GLESRenderer(android_app* p_State);
    ~GLESRenderer();

    virtual bool OnInit() override;
    virtual void Update(float DeltaTime) override;
    virtual void OnAbort()override ;

    void SetupObjects();

private:

    bool InitDisplay();
    bool InitSurface();
    bool InitContext();

private:

    std::vector<class Renderable*> mObjects;

    EGLDisplay m_Display;
    EGLContext m_Context;
    EGLSurface m_Surface;
    EGLConfig  m_Config;

    int m_Width;
    int m_Height;

    android_app* m_State;

    class SpriteRenderer* mSprite;
    class Texture2D* mTexture;
};


#endif //BURNOUTENGINE_GLESRenderer_HPP
