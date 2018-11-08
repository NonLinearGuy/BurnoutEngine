//
// Created by Ankit Singh on 25-09-2018.
//

#include<android/log.h>
#include "BurnoutApp.hpp"
#include "Triangle.hpp"
#include<FileReader.hpp>
#include"android_fopen.h"

extern "C"
{

void android_main(android_app *state) {
    auto sharedAppState = std::make_shared<android_app>();
    sharedAppState.reset(state);

    FileReader::GetInstance()->sAssetManager = state->activity->assetManager;
    android_fopen_set_asset_manager(state->activity->assetManager);

    BurnoutApp *app = new BurnoutApp(sharedAppState);
    if (app->Initialize())
        app->Run();
    else
        __android_log_print(10, "BurnoutEngine", "Failed to initialize GLES application");
    delete app;
}

}


