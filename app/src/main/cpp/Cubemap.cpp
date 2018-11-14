//
// Created by Ankit Singh on 07-11-2018.
//

#include "Cubemap.hpp"
#include"glm/glm.hpp"
#include<vector>
#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"

Cubemap::Cubemap() : Renderable(glm::vec3(0.0f)) {
    mTextureID = 0;
    mModel = glm::mat4();
  }

Cubemap::~Cubemap() {
    glDeleteTextures(1,&mTextureID);
}


void Cubemap::Init() {
    Renderable::Init();

    mShaderProgram.Create("shaders/cubemap_vs.glsl","shaders/cubemap_fs.glsl");
    LoadTextures();
    LoadVertices();
}

void Cubemap::LoadVertices() {
    float skyboxVertices[] = {
            // positions
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f,  1.0f
    };

    glGenVertexArrays(1,&mVAO);
    glBindVertexArray(mVAO);

    glGenBuffers(1,&mVBO);
    glBindBuffer(GL_ARRAY_BUFFER,mVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(skyboxVertices),skyboxVertices,GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);

    glBindVertexArray(0);
}

void Cubemap::LoadTextures() {
    std::vector<std::string> mFaceNames;
    mFaceNames.push_back("right");
    mFaceNames.push_back("left");
    mFaceNames.push_back("top");
    mFaceNames.push_back("bottom");
    mFaceNames.push_back("back");
    mFaceNames.push_back("front");

    glGenTextures(1,&mTextureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP,mTextureID);

    int width,height,channels;
    unsigned char* image = nullptr;

    for(int index = 0 ; index < 6 ; ++index)
    {
        image = stbi_load(("skybox/" + mFaceNames[index] + ".tga").c_str(),&width,&height,&channels,0);
        GLenum format = channels==4?GL_RGBA:GL_RGB;
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + index,0,format,width,height,0,format,GL_UNSIGNED_BYTE,image);
        stbi_image_free(image);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_CUBE_MAP,0);
}

void Cubemap::SetupShaderValues() {

    mShaderProgram.Set1i("cubemap",0);
    mShaderProgram.SetMat4("model",mModel);
}


void Cubemap::Tick(double Deltatime) {
    Renderable::Tick(Deltatime);

    static float angle = 0.0;
    angle+=1.0;
    mModel = glm::mat4();
    mModel = glm::rotate(mModel, glm::radians(angle),glm::vec3(.5f,.5f,0.0f));
}

void Cubemap::Render() {
    Renderable::Render();

    glDepthFunc(GL_LEQUAL);
    mShaderProgram.Use();
    SetupShaderValues();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP,mTextureID);
    glBindVertexArray(mVAO);
    glDrawArrays(GL_TRIANGLES,0,36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);

}

