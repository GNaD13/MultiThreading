#include "RecognitionWorker.hpp"
#include "AIAppAnpr.hpp"
#include <string>
#include <iostream>

RecognitionWorker::RecognitionWorker(AIApplication* owner, int threadNum)
    : Worker(owner)
    , mThreadNum(threadNum)
{

}

RecognitionWorker::~RecognitionWorker()
{

}

void RecognitionWorker::runThread()
{
    mThread = std::thread(&RecognitionWorker::threadFunc, this);
}

void RecognitionWorker::threadFunc()
{
    while(mIsRunning)
    {
        // Temp Variable
        int temp = -1;

        // Get data from share memory
        auto appAI = GetAIApplication();
        std::unique_lock<std::mutex> lock(appAI->mMutex);
        if(appAI->GetState() == AIApplication::State::RECOGNIZE && !appAI->IsDataEventEmpty())
        {
            temp = appAI->mDataEvent.back();
            appAI->mDataEvent.pop_back();
        }
        lock.unlock();

        // TODO: Logic AI Recognize
        /*--------------------------------------------------------*/




        /*--------------------------------------------------------*/
        // Callback result
        EventCallbackFunc callbackFunc = appAI->GetEventCallbackFunc();
        std::string temp1 = "Recognition";
        callbackFunc(temp1, temp);

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}