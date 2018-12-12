//
// Created by Ankit Singh on 07-11-2018.
//

#include "Camera.hpp"
#include <math.h>


Camera::Camera() : mPosition(0.0f,1.0f,3.0f),mFront(0.0f,0.0f,-1.0f),mSenstivity(10.0f){
    mIsFirstTouch = true;
    pitch = -90.f;
    yaw = 0.0f;
}

Camera::~Camera() {}


glm::mat4 Camera::GetView() const
{
    return mView;
}


void Camera::OnTouchRelease(float x, float y)
{
    mIsFirstTouch = true;
}

void Camera::OnTouch(float x, float y)
{
    if(mIsFirstTouch)
    {
        mLastTouchPosition = glm::vec2(x,y);
        mIsFirstTouch = false;
        return;
    }

    float xoffset = x - mLastTouchPosition.x;
    float yoffset = y - mLastTouchPosition.y;
    yaw += xoffset * .005f;
    pitch+= yoffset * .005f;

    mLastTouchPosition = glm::vec2(x,y);
    mFront.x = cos(yaw) * cos(pitch);
    mFront.y = sin(pitch);
    mFront.z = sin(yaw) * cos(pitch);

    glm::normalize(mFront);

    mView = glm::mat4();
    mView = glm::lookAt(mPosition,mPosition + mFront,glm::vec3(0.0f,1.0f,0.0f));
}