//
// Created by Ankit Singh on 02-10-2018.
//

#include "BurnoutApp.hpp"

//processes
#include"Delay.hpp"
#include"GLESRenderer.hpp"
#include"android/log.h"

BurnoutApp::BurnoutApp(std::shared_ptr<android_app> state) : m_State(state),m_Kernel(ProcessHandler::GetInstance())
{
    m_State->onAppCmd = HandleCommand;
    m_State->userData = static_cast<void*>(this);
}

BurnoutApp::~BurnoutApp()
{
}

bool BurnoutApp::Initialize()
{
    bool RetValue = true;

   // m_Kernel->AddProcess(std::shared_ptr<Delay>(new Delay(10.0f)));


    return RetValue;
}

void BurnoutApp::Run() {
    int events;
    struct android_poll_source *pSource;
    int result = 0;
    while (true)
    {
      result = ALooper_pollAll(0, 0, &events, (void**)&pSource);
        if (result >= 0) {
            if (pSource)
                pSource->process(m_State.get(), pSource);

            if(m_State->destroyRequested) {
                m_Kernel->AbortAll();
                return;
            }
            }

        m_Kernel->Tick();
    }

}


//Static methods

void createTheRenderer(android_app* state)
{

}
void BurnoutApp::HandleCommand(android_app *appState, int32_t Command)
{
    BurnoutApp* app = static_cast<BurnoutApp*>(appState->userData);

    switch(Command)
    {
        case APP_CMD_START:
            break;
        case APP_CMD_STOP:
            break;
        case APP_CMD_INIT_WINDOW: {
            app->m_Kernel->AddProcess(std::shared_ptr<GLESRenderer>(new GLESRenderer(appState)));
            break;
        }
        case APP_CMD_PAUSE:
            break;
        case APP_CMD_RESUME:
            break;
        case APP_CMD_DESTROY:
            break;
        default:
            break;
    }

}
