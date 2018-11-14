//
// Created by Ankit Singh on 03-11-2018.
//

#ifndef BURNOUTENGINE_RENDERABLE_HPP
#define BURNOUTENGINE_RENDERABLE_HPP

#include<glm/glm.hpp>
#include<ShaderProgram.hpp>
#include<glm/gtc/matrix_transform.hpp>

class Renderable
{
public:
    Renderable(const glm::vec3 worldPosition) : mPosition(worldPosition),mModel(),mShaderProgram(), mVAO(-1),mVBO(-1),mEBO(-1) {}
    virtual ~Renderable(){}
    virtual void Init(){}
    virtual void Destroy(){mShaderProgram.Delete();}
    virtual void Render(){}
    virtual void Tick(double DeltaTime){}

    inline ShaderProgram GetShader()
    {
        return mShaderProgram;
    }
protected:
    glm::mat4 mModel;
    glm::vec3 mPosition;
    GLuint mVAO;
    GLuint mEBO;
    GLuint mVBO;
    ShaderProgram mShaderProgram;
};

#endif //BURNOUTENGINE_RENDERABLE_HPP
