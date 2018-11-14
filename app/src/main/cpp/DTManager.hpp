//
// Created by Ankit Singh on 11-11-2018.
//

#ifndef BURNOUTENGINE_DTMANAGER_HPP
#define BURNOUTENGINE_DTMANAGER_HPP

#include<chrono>

typedef std::chrono::steady_clock Clock;
class DTManager {

public:
    static DTManager* GetInstance()
    {
        static DTManager instance;
        return &instance;
    }
    double GetDeltaTimeInMS();
    double GetDeltaTimeInSeconds();
    void Update();
    void Reset();
private:
    DTManager();
    std::chrono::steady_clock::time_point mCurrentTime,mLastTime;
    double mDeltaTime;
};


#endif //BURNOUTENGINE_DTMANAGER_HPP
