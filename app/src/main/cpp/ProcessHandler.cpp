//
// Created by Ankit Singh on 03-10-2018.
//

#include "ProcessHandler.hpp"
#include<algorithm>

ProcessHandler::ProcessHandler()
{
    m_ActiveProcessList.reserve(START_LIST_SIZE);
}

void ProcessHandler::Update(float DeltaTime)
{
    for(auto iter = m_ActiveProcessList.begin() ; iter != m_ActiveProcessList.end() ; )
    {
        auto tempIter = iter;
        SharedProcess currentProcess = *tempIter;
        ++iter;
        EProcessState  currentState = currentProcess->GetState();

        if(EProcessState::NOT_INITIALIZED == currentState)
            currentProcess->OnStart();

        if(EProcessState::RUNNING == currentState)
            currentProcess->Update(DeltaTime);

        if(currentProcess->IsDead())
        {
            switch(currentState)
            {
                case EProcessState ::SUCECCEDED:
                    currentProcess->OnSuccess();
                    SharedProcess pChild = currentProcess->RemoveChild();
                    if(pChild)
                        AddProcess(pChild);
                    break;
                case EProcessState ::FAILED:
                    currentProcess->OnFailed();
                    break;
                case EProcessState ::ABORTED:
                    currentProcess->OnAbort();
                    break;
            }

            m_ActiveProcessList.erase(tempIter);
        }
    }
}


void ProcessHandler::AddProcess(SharedProcess NewProcess)
{
    m_ActiveProcessList.push_back(NewProcess);
}

