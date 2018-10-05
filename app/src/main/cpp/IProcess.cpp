//
// Created by Ankit Singh on 02-10-2018.
//

#include "IProcess.hpp"

unsigned IProcess::sProcessCounter = 0;

IProcess::IProcess()
: m_CurrentState(EProcessState::NOT_INITIALIZED),
  m_ID(sProcessCounter++)
{

}

IProcess::~IProcess()
{
    if(m_Child)
    {
        m_Child->OnAbort();
    }
}

SharedProcess IProcess::RemoveChild()
{
    if(m_Child)
    {
        SharedProcess Child = m_Child;
        m_Child.reset();
        return Child;
    }
    return SharedProcess();
}




