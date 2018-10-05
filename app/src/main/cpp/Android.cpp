//
// Created by Ankit Singh on 25-09-2018.
//

#include"Android.hpp"
#include<android/log.h>

bool Android::mStop = false;

Android::Android(android_app *state) : mState(state)
{
    state->onAppCmd = Android::HandleCommand;
}

Android::~Android()
{

}

void Android::Update()
{
    int Events;
    android_poll_source* Source;

    int Result = 0;
    while(1)
    {
        Result = ALooper_pollAll(0,0,&Events,(void**)Source);
            break;
    }
}

void Android::HandleCommand(android_app *pState, int32_t cmd)
{
switch(cmd)
{
    case APP_CMD_STOP:
        mStop = true;
        break;
}

}


