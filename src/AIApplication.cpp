#include "AIApplication.hpp"
#include "Application.hpp"
#include "AIAppAnpr.hpp"
#include "Worker.hpp"
#include <algorithm>

AIApplication* AIApplication::InitAiApplication(AIAppType& type, Application* app)
{
    switch (type)
    {
        case AIAppType::AI_FACEMASK_DETECTION:
            return nullptr;
        case AIAppType::AI_FACE_RECOGNITION:
            return nullptr;
        case AIAppType::AI_HUMAN_DETECTION:
            return nullptr;
        case AIAppType::AI_ITS:
            return new AIAppAnpr(app);
        case AIAppType::AI_FIRE_DETECTION:
            return nullptr;
        case AIAppType::AI_SOCIAL_DISTANCING:
            return nullptr;
        default:
            return nullptr;
            break;
    }
}

AIApplication::AIApplication(Application* app)
    : mApp(app)
    , mNumThreads(5)
    , mState(State::READY)
    , mIsRunning(false)
{
    mApp->AddAIApplication(this);
}

AIApplication::~AIApplication()
{
    mApp->RemoveAIApplication(this);
    while(!mWorker.empty())
    {
        mWorker.back()->stop();
        delete mWorker.back();
    }
}

void AIApplication::Run()
{
    for(auto worker : mWorker)
    {
        worker->runThread();
    }
}

void AIApplication::Shutdown()
{
    while(!mWorker.empty())
        delete mWorker.back();
}

void AIApplication::AddWorker(Worker* worker)
{
    mWorker.emplace_back(worker);
}

void AIApplication::RemoveWorker(Worker* worker)
{
    auto iter = std::find(mWorker.begin(), mWorker.end(), worker);
    if(iter != mWorker.end())
    {
        mWorker.erase(iter);
    }
}
