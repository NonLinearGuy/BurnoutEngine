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

    RESUMED,

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
    virtual bool OnInit() {return true;}
    virtual void OnPause() {}
    virtual void OnResume() {}
    virtual void OnAbort() {}
    virtual void OnFailed() {}
    virtual void OnSuccess() {}
    virtual void Update(float DeltaTime) = 0;

    virtual void OnTouch(float X,float Y){};
    virtual void OnTouchRelease(float x, float y){};
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

inline void IProcess::SetState(EProcessState pCurrentState)
{
    m_CurrentState = pCurrentState;
}
#endif //BURNOUTENGINE_PROCESS_HPP
