//
// Created by Ankit Singh on 25-09-2018.
//

#include<android/log.h>
#include <Application.hpp>
#include"GLESApp.hpp"
#include"AndroidCallbacksManager.hpp"

extern "C"
{
    void android_main(struct android_app* state)
    {
       Application* app = new GLESApp(state);

        if(app->Initialize())
        {
            AndroidCallbacksManager::SetupCallbacks(state,app);
            app->Run();
        }
        else
        __android_log_print(10,"BurnoutEngine","Failed to initialize GLES application");
        delete app;
    }

}


