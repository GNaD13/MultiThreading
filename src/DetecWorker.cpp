#include "DetecWorker.hpp"
#include "AIAppAnpr.hpp"
#include "AIApplication.hpp"
#include "Application.hpp"
#include <iostream>

DetecWorker::DetecWorker(AIApplication* owner)
    : Worker(owner)
{

}

DetecWorker::~DetecWorker()
{

}

void DetecWorker::runThread()
{
    mThread = std::thread(&DetecWorker::threadFunc, this);
}

void DetecWorker::threadFunc()
{
    while(mIsRunning)
    {
        auto appAI = GetAIApplication();
        auto app = GetAIApplication()->GetApplication();
        std::unique_lock<std::mutex> lock(appAI->mMutex);
        if(appAI->GetState() == AIApplication::State::READY)
        {
            // Switch state
            appAI->SetState(AIApplication::State::DETECTION);
            // Get data
            int temp = app->GetData();
            appAI->SetData(temp);
            // push data to share memory
            for(int i = 0; i < temp; i++)
            {
                appAI->mDataEvent.emplace_back(i);
            }
            // Switch state
            appAI->SetState(AIApplication::State::RECOGNIZE);
        }

        // If done recognize, switch state
        if(appAI->GetState() == AIApplication::State::RECOGNIZE && appAI->IsDataEventEmpty())
        {
            appAI->SetState(AIApplication::State::READY);
        }
        lock.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}