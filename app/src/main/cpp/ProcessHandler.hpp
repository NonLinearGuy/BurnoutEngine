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
        static auto instance = std::shared_ptr<ProcessHandler>(new ProcessHandler());
        return instance;
    }

    void AddProcess(SharedProcess NewProcess);
    void AbortAll();
    void Pause();
    void Resume();
    inline unsigned GetProcessCount();

    void Tick();

    ~ProcessHandler();
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