//
// Created by Ankit Singh on 11-11-2018.
//

#include "DTManager.hpp"

using namespace std;

double DTManager::GetDeltaTimeInMS()
{
return mDeltaTime;
}

double DTManager::GetDeltaTimeInSeconds()
{
 return mDeltaTime * .001;
}

void DTManager::Update() {
    mCurrentTime = Clock::now();
    mDeltaTime = std::chrono::duration_cast<std::chrono::milliseconds>((mCurrentTime - mLastTime)).count();
    mLastTime = mCurrentTime;
}

DTManager::DTManager() : mDeltaTime(0.0){

}

void DTManager::Reset() {
mLastTime = mCurrentTime = Clock::now();
}
