//
// Created by Ankit Singh on 25-09-2018.
//

#ifndef BURNOUTENGINE_ANDROID_HPP
#define BURNOUTENGINE_ANDROID_HPP

#include<android_native_app_glue.h>

class Android
{

public:
    Android(android_app* state);
    ~Android();
    void Update();
    static void HandleCommand(android_app* pState,int32_t cmd);

private:
    android_app* mState;
    static bool mStop;
};

#endif //BURNOUTENGINE_ANDROID_HPP
