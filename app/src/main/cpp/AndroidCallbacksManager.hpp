//
// Created by Ankit Singh on 05-10-2018.
//

#ifndef BURNOUTENGINE_ANDROIDCALLBACKSMANAGER_HPP
#define BURNOUTENGINE_ANDROIDCALLBACKSMANAGER_HPP

class Application;
struct android_app;

class AndroidCallbacksManager {
public:
    static void SetupCallbacks(android_app* pState,Application* app);
private:
    static void HandleCommand(android_app* app,int32_t cmd);
    static void HandleInput();
    static Application* m_App;
};


#endif //BURNOUTENGINE_ANDROIDCALLBACKSMANAGER_HPP
