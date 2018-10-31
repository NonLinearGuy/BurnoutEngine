//
// Created by Ankit Singh on 31-10-2018.
//

#ifndef BURNOUTENGINE_TEXTUREDPLANE_HPP
#define BURNOUTENGINE_TEXTUREDPLANE_HPP

#include<SceneObject.cpp>

class TexturedPlane : public SceneObject{
public:
    void Update()override;
    void Draw()override;
private:

};


#endif //BURNOUTENGINE_TEXTUREDPLANE_HPP
