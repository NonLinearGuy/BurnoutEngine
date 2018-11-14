//
// Created by Ankit Singh on 03-11-2018.
//

#ifndef BURNOUTENGINE_TEXTUREDPLANE_HPP
#define BURNOUTENGINE_TEXTUREDPLANE_HPP

#include<Renderable.hpp>
#include "Texture2D.h"

class TexturedPlane : public Renderable{
public:
    TexturedPlane(const glm::vec3& worldPosition);
    void Init()override;
    void Destroy()override;
    void Tick(double DeltaTime)override;
    void Render() override;
    void SetShaderValues();
private:
    Texture2D grass0;
    Texture2D path1;
    Texture2D blendFactor2;
    Texture2D  normalMap3;
};


#endif //BURNOUTENGINE_TEXTUREDPLANE_HPP
