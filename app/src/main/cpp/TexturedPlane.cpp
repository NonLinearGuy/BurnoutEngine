//
// Created by Ankit Singh on 03-11-2018.
//

#include "TexturedPlane.hpp"
#include"stb_image.h"


TexturedPlane::TexturedPlane(const glm::vec3& worldPosition,const glm::vec3& color) : Renderable(worldPosition), mColor(color)
{
    mModel = glm::mat4();
    mModel = glm::translate(mModel, glm::vec3(0.0f,0.0f,-5.0f));
    mModel = glm::scale(mModel,glm::vec3(5.0f,5.0f,5.0f));

    texture = Texture2D();
    texture.CreateTexture("textures/sprite_enemy.png");
}

void TexturedPlane::Init() {
    Renderable::Init();

    mShaderProgram.Create("shaders/plane_vs.glsl","shaders/plane_fs.glsl");

    float attribs[] =
            {
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



void TexturedPlane::Tick()
{


}

void TexturedPlane::Render()
{
    mShaderProgram.Use();
    SetShaderValues();
    glActiveTexture(GL_TEXTURE0);
    texture.Bind();
    glBindVertexArray(mVAO);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
    glBindVertexArray(0);
}

void TexturedPlane::SetShaderValues()
{
    mShaderProgram.SetMat4("model",mModel);
    mShaderProgram.SetVec3("color",mColor);
}


void TexturedPlane::Destroy() {
    Renderable::Destroy();

    mShaderProgram.Delete();
}