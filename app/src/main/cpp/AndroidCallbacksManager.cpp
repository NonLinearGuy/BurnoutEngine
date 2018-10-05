//
// Created by Ankit Singh on 05-10-2018.
//

#include "AndroidCallbacksManager.hpp"
#include"android_native_app_glue.h"
#include"Application.hpp"


void AndroidCallbacksManager::SetupCallbacks(android_app *pState, Application *app)
{
    m_App = app;
    pState->onAppCmd = HandleCommand;
}

void AndroidCallbacksManager::HandleCommand(android_app * app, int32_t cmd)
{
    m_App->HandleCommand(cmd);
}