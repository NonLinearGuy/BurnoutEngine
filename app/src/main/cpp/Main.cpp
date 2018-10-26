//
// Created by Ankit Singh on 25-09-2018.
//

#include<android/log.h>
#include "BurnoutApp.hpp"

extern "C"
{
    void android_main(android_app* state)
    {
        auto sharedAppState = std::make_shared<android_app>();
        sharedAppState.reset(state);

       BurnoutApp* app = new BurnoutApp(sharedAppState);

        if(app->Initialize())
            app->Run();
        else
        __android_log_print(10,"BurnoutEngine","Failed to initialize GLES application");
        delete app;
    }

}


