//
// Created by Ankit Singh on 03-11-2018.
//

#ifndef BURNOUTENGINE_TEXTUREDPLANE_HPP
#define BURNOUTENGINE_TEXTUREDPLANE_HPP

#include<Renderable.hpp>
#include "Texture2D.h"
class TexturedPlane : public Renderable{
public:
    TexturedPlane(const glm::vec3& worldPosition,const glm::vec3& color);
    void Init()override;
    void Destroy()override;
    void Tick()override;
    void Render() override;
    void SetShaderValues();

private:

    glm::vec3 mColor;

    Texture2D texture;
};


#endif //BURNOUTENGINE_TEXTUREDPLANE_HPP
