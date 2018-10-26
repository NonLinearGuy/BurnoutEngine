//
// Created by Ankit Singh on 06-10-2018.
//

#ifndef BURNOUTENGINE_DELAY_HPP
#define BURNOUTENGINE_DELAY_HPP

#include"IProcess.hpp"


class Delay : public IProcess
{
public:
    Delay(float maxTime);
    bool OnInit()override;
    void Update(float DeltaTime)override;
    void OnSuccess()override ;
    private:
    float m_Elasped;
    float m_MaxTime;
};


#endif //BURNOUTENGINE_DELAY_HPP
