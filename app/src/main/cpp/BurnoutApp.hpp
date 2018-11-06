//
// Created by Ankit Singh on 02-10-2018.
//

#ifndef BURNOUTENGINE_BurnoutApp_HPP
#define BURNOUTENGINE_BurnoutApp_HPP

#include"android_native_app_glue.h"
#include"ProcessHandler.hpp"

class BurnoutApp
{
public:
    BurnoutApp(std::shared_ptr<android_app> state);
    ~BurnoutApp();
    bool Initialize();
    void Run();
    static void HandleCommand(android_app* appState,int32_t Command);

private:
    std::shared_ptr<android_app> m_State;
public:
    std::shared_ptr<ProcessHandler> m_Kernel;
};


#endif //BURNOUTENGINE_BurnoutApp_HPP
