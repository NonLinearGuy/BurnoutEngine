//
// Created by Ankit Singh on 02-10-2018.
//

#ifndef BURNOUTENGINE_APPLICATION_HPP
#define BURNOUTENGINE_APPLICATION_HPP

#include"android_native_app_glue.h"

class Application
{
public:
    Application(android_app *state);
    virtual ~Application();
    virtual bool Initialize() = 0;
    virtual void Run() = 0;
    virtual void HandleCommand(int32_t Command) = 0;
protected:
    android_app* m_State;
};


#endif //BURNOUTENGINE_APPLICATION_HPP
