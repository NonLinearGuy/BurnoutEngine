//
// Created by Ankit Singh on 07-11-2018.
//

#ifndef BURNOUTENGINE_CAMERA_HPP
#define BURNOUTENGINE_CAMERA_HPP

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

class Camera
{

public:
    Camera();
    ~Camera();

    void OnTouch(float x,float y);
    void OnTouchRelease(float x, float y);

    glm::mat4 GetView();
private:

    bool mIsFirstTouch;
    glm::vec2 mLastTouchPosition;
    glm::vec3 mPosition;
    glm::vec3 mFront;
    float mSenstivity;

    glm::mat4 mView;
    float pitch;
    float yaw;
};


#endif //BURNOUTENGINE_CAMERA_HPP
