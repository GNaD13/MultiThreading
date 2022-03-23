#include "Application.hpp"
#include "AIApplication.hpp"
#include <algorithm>
#include <unistd.h>

Application::Application()
    : mIsRunning(true)
    , mData(0)
{

}

Application::~Application()
{
    
}

void Application::Begin()
{

}

bool Application::Initialize(const EventCallbackFunc &callback, AIAppType& type, int numThread)
{
    auto iter = mAIAppMap.find(type);
    if(iter != mAIAppMap.end())
    {
        std::cerr << "AI Type already initialize" << std::endl;
        return false;
    }

    AIApplication* app = AIApplication::InitAiApplication(type, this);
    if(app == nullptr)
    {
        std::cerr << "AI Type not support" << std::endl;
        return false;
    }

    if(!app->Initialize(numThread))
    {
        std::cerr << "Failed to initialize AI Application" << std::endl;
        return false;
    }

    app->SetEventCallbackFunc(callback);

    mAIAppMap.emplace(type, app);
    return true;
}

void Application::Run()
{
    for(auto AIApp : mAIApp)
    {
        if(!AIApp->GetStatus())
        {
            AIApp->SetStatus(true);
            AIApp->Run();
        }
    }
}

bool Application::DeInitialize(AIAppType& type)
{
    auto iter = mAIAppMap.find(type);
    if(iter != mAIAppMap.end())
    {
        AIApplication* app = iter->second;
        delete app;
        mAIAppMap.erase(iter);
        return true;
    }
    std::cerr << "AI Type not initialize yet!" << std::endl;
    return false;
}

void Application::End()
{
    while(!mAIApp.empty())
    {
        delete mAIApp.back();
    }
}

void Application::AddAIApplication(AIApplication* app)
{
    mAIApp.emplace_back(app);
}

void Application::RemoveAIApplication(AIApplication* app)
{
    auto iter = std::find(mAIApp.begin(), mAIApp.end(), app);
    if(iter != mAIApp.end())
    {
        mAIApp.erase(iter);
    }
}