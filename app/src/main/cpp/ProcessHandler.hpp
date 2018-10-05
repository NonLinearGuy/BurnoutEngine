//
// Created by Ankit Singh on 03-10-2018.
//

#ifndef BURNOUTENGINE_PROCESSHANDLER_HPP
#define BURNOUTENGINE_PROCESSHANDLER_HPP

#include"IProcess.hpp"
#include<memory>
#include<vector>

using SharedProcessList = std::vector< SharedProcess >;

class ProcessHandler
{
public:
    static std::shared_ptr<ProcessHandler> GetInstance()
    {
        static auto instance = std::make_shared<ProcessHandler>();
        return instance;
    }

    void AddProcess(SharedProcess NewProcess);
    void ClearAll();
    void Pause();
    void Resume();
    inline unsigned GetProcessCount();

    void Update(float DeltaTime);

private:

    ProcessHandler();
    SharedProcessList m_ActiveProcessList;
    const int START_LIST_SIZE = 50;
};


#endif //BURNOUTENGINE_PROCESSHANDLER_HPP


inline unsigned ProcessHandler::GetProcessCount()
{
    return m_ActiveProcessList.size();
}