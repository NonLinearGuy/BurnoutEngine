//
// Created by Ankit Singh on 06-10-2018.
//

#include "Delay.hpp"
#include"android/log.h"

Delay::Delay(float maxTime) : m_MaxTime(maxTime),m_Elasped(0.0f){}

bool Delay::OnInit()
{
    SetState(EProcessState::RUNNING);
    return true;
}

void Delay::Update(float DeltaTime)
{
    m_Elasped+=1;
    __android_log_print(100,"engine_log","Time : %d",(int)m_Elasped);
    if( m_Elasped > m_MaxTime )
        SetState(EProcessState::SUCECCEDED);
}

void Delay::OnSuccess()
{
    __android_log_print(10,"engine_log","DAMN!!!!");
}

