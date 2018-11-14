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

    glm::vec3 GetPosition() const
    {
        return mPosition;
    }

    glm::mat4 GetView() const;

    void Update(float deltaTime)
    {
      /*  static float angle = .1f;
        angle+=.01;
        mPosition.x = 3.0f * cos(angle);
        mPosition.z = 3.0f * sin(angle);*/

        //mView = glm::lookAt(mPosition,mPosition + mFront,glm::vec3(0.0f,1.0f,0.0f));
    }

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
