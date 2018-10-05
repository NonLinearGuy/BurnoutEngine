//
// Created by Ankit Singh on 02-10-2018.
//

#ifndef BURNOUTENGINE_IPROCESS_HPP
#define BURNOUTENGINE_IPROCESS_HPP

#include<memory>

enum class EProcessState
{
    NOT_INITIALIZED = 0,

    RUNNING,
    PAUSED,

    ABORTED,
    SUCECCEDED,
    FAILED
};

class IProcess;
using SharedProcess = std::shared_ptr<IProcess>;

class IProcess
{
public:
    IProcess();
    ~IProcess();
    virtual bool OnStart() {}
    virtual bool OnPause() {}
    virtual bool OnResume() {}
    virtual void OnAbort() {}
    virtual void OnFailed() {}
    virtual void OnSuccess() {}
    virtual void Update(float DeltaTime) = 0;

    SharedProcess RemoveChild();

    inline EProcessState GetState();
    inline void AddChild(SharedProcess pChild);
    inline void SetState(EProcessState pCurrentState);
    inline bool IsDead();
    inline bool IsAlive();
    inline unsigned GetID();

protected :
    EProcessState m_CurrentState;
    unsigned m_ID;
    SharedProcess m_Child;

private:
    static unsigned sProcessCounter;
};

//inlines
inline EProcessState IProcess::GetState()
{
return m_CurrentState;
}

inline unsigned IProcess::GetID()
{
    return m_ID;
}

inline bool IProcess::IsDead()
{
    return (EProcessState::SUCECCEDED == m_CurrentState ||
            EProcessState::ABORTED == m_CurrentState ||
            EProcessState::FAILED == m_CurrentState
    );
}

inline bool IProcess::IsAlive()
{
    return (EProcessState::RUNNING == m_CurrentState);
}


inline void IProcess::AddChild(SharedProcess pChild)
{
    if(m_Child)
        m_Child->AddChild(pChild);
    else
        m_Child = pChild;
}

void SetState(EProcessState pCurrentState)
{
    m_CurrentState = pCurrentState;
}
#endif //BURNOUTENGINE_PROCESS_HPP
