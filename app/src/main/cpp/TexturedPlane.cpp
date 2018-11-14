//
// Created by Ankit Singh on 03-11-2018.
//

#include "TexturedPlane.hpp"


TexturedPlane::TexturedPlane(const glm::vec3& worldPosition) : Renderable(worldPosition)
{
    mModel = glm::mat4();
    mModel = glm::rotate(mModel,-90.0f,glm::vec3(1.0f,0.0f,0.0f));
    mModel = glm::translate(mModel, glm::vec3(0.0f,0.0f,0.0f));
    mModel = glm::scale(mModel,glm::vec3(30.0f));

    grass0 = Texture2D();
    grass0.CreateTexture("textures/grass.png",true);
    path1 = Texture2D();
    path1.CreateTexture("textures/pathDiffuse.png",true);
    blendFactor2 = Texture2D();
    blendFactor2.CreateTexture("textures/blendFactor.png",true);
    normalMap3 = Texture2D();
    normalMap3.CreateTexture("textures/pathNormal.png",true);
}

void TexturedPlane::Init() {
    Renderable::Init();

    mShaderProgram.Create("shaders/plane_vs.glsl","shaders/plane_fs.glsl");

    float attribs[] = {
                    -0.5f,-.5f,0.0f, 0.0f,0.0f,
                    0.5f,-0.5f,0.0f, 1.0f,0.0f,
                    0.5f,0.5f,0.0f,  1.0f,1.0f,
                    -0.5f,0.5f,0.0f , 0.0f,1.0f
            };

    int indices[] = {0,1,3,1,2,3};

    glGenVertexArrays(1,&mVAO);
    glBindVertexArray(mVAO);

    glGenBuffers(1,&mVBO);
    glBindBuffer(GL_ARRAY_BUFFER,mVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(attribs),attribs,GL_STATIC_DRAW);

    glGenBuffers(1,&mEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(float) * 5,0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(float) * 5,(void*)(sizeof(float) * 3));

    glBindVertexArray(0);
}



void TexturedPlane::Tick(double Deltatime)
{
Renderable::Tick(Deltatime);

}

void TexturedPlane::Render()
{

Renderable::Render();
    mShaderProgram.Use();
    SetShaderValues();
    grass0.BindToUnit(GL_TEXTURE0);
    path1.BindToUnit(GL_TEXTURE1);
    blendFactor2.BindToUnit(GL_TEXTURE2);
    normalMap3.BindToUnit(GL_TEXTURE3);
    glBindVertexArray(mVAO);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
    glBindVertexArray(0);

}

void TexturedPlane::SetShaderValues()
{
    mShaderProgram.SetMat4("model",mModel);
     mShaderProgram.Set1i("grass0",0);
    mShaderProgram.Set1i("path1",1);
    mShaderProgram.Set1i("blendFactor2",2);
    mShaderProgram.Set1i("normalMap3",3);

    mShaderProgram.SetVec3("uLightPosition",glm::vec3(0.0f,1.0f,0.0f));
    mShaderProgram.SetVec3("lightColor", glm::vec3(1.0f,1.0f,1.0f));
    mShaderProgram.Set1f("lightIntensity", 8.0f);
    mShaderProgram.Set1f("constant",.001f);
    mShaderProgram.Set1f("linear",0.0f);
    mShaderProgram.Set1f("quadratic",.5f);
}


void TexturedPlane::Destroy() {
    Renderable::Destroy();

    mShaderProgram.Delete();
}
