//
// Created by Ankit Singh on 03-10-2018.
//

#include "ProcessHandler.hpp"
#include<algorithm>

ProcessHandler::ProcessHandler()
{
    m_ActiveProcessList.reserve(START_LIST_SIZE);
}

ProcessHandler::~ProcessHandler()
{
    m_ActiveProcessList.clear();
}


void ProcessHandler::AbortAll()
{
    for(auto iter = m_ActiveProcessList.begin() ; iter != m_ActiveProcessList.end() ; )
    {
        auto process = *iter;
        process->OnAbort();
        iter = m_ActiveProcessList.erase(iter);
    }

}

void ProcessHandler::Pause()
{
    for(auto process : m_ActiveProcessList)
    {
        process->SetState(EProcessState::PAUSED);
        process->OnPause();
    }
}

void ProcessHandler::Resume()
{
    for(auto process : m_ActiveProcessList)
    {
        process->SetState(EProcessState::RESUMED);
        process->OnResume();
    }
}

void ProcessHandler::Tick()
{
    for(auto iter = m_ActiveProcessList.begin() ; iter != m_ActiveProcessList.end() ; )
    {
        auto process = *iter;
        auto state = process->GetState();

        if(EProcessState::RUNNING == state)
            process->Update(.001f);

        if(process->IsDead())
        {
            switch(state)
            {
                case EProcessState::SUCECCEDED: {
                    auto childProcess = process->RemoveChild();
                    if (childProcess) {
                        AddProcess(childProcess);
                    }
                    process->OnSuccess();
                    break;
                }
                case EProcessState::FAILED:
                    process->OnFailed();
                    break;
                case EProcessState ::ABORTED:
                    process->OnAbort();
                    break;
                default:
                    break;
            };

            iter = m_ActiveProcessList.erase(iter);
        }
        else
            ++iter;

    }

}


void ProcessHandler::AddProcess(SharedProcess NewProcess)
{
    if(EProcessState::NOT_INITIALIZED == NewProcess->GetState())
        NewProcess->OnInit();
    m_ActiveProcessList.push_back(NewProcess);
}

