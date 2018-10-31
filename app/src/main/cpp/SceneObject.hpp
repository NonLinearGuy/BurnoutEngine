//
// Created by Ankit Singh on 31-10-2018.
//

#ifndef BURNOUTENGINE_SCENEOBJECT_HPP
#define BURNOUTENGINE_SCENEOBJECT_HPP


#include<glm/glm.hpp>

class SceneObject {
public:
    virtual void Draw(){}
    virtual void Update(){}
protected:
    glm::vec3 mPosition;
};


#endif //BURNOUTENGINE_SCENEOBJECT_HPP
