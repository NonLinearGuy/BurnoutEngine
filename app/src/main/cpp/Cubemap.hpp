//
// Created by Ankit Singh on 07-11-2018.
//

#ifndef BURNOUTENGINE_CUBEMAP_HPP
#define BURNOUTENGINE_CUBEMAP_HPP

#include "Renderable.hpp"

class Cubemap : public Renderable{

public:

    Cubemap();
    ~Cubemap();

    void Init();
    void LoadVertices();
    void LoadTextures();
    void SetupShaderValues();
    void Tick(double deltaTime)override;
    void Render()override;

private:

    GLuint mTextureID;
    GLuint mVAO;
    GLuint mVBO;
    glm::mat4 mModel;


};


#endif //BURNOUTENGINE_CUBEMAP_HPP
