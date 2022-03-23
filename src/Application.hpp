#ifndef Application_hpp
#define Application_hpp

#include <iostream>
#include <vector>
#include <unordered_map>
#include "DetecWorker.hpp"
#include "RecognitionWorker.hpp"
#include <mutex>
#include "Define.hpp"

class AIApplication;
enum class AIAppType;

class Application
{
public:
    Application();
    ~Application();

    void Begin();
    bool Initialize(const EventCallbackFunc &callback, AIAppType& type, int numThread = 5);
    void Run();
    bool DeInitialize(AIAppType& type);
    void End();

    void SetData(int data) { mData = data; }
    int GetData() const { return mData; }

    void AddAIApplication(AIApplication* AIApp);
    void RemoveAIApplication(AIApplication* AIApp);
private:
    bool mIsRunning;

    std::vector<AIApplication*> mAIApp;
    std::unordered_map<AIAppType, AIApplication*> mAIAppMap;

    int mData;
};

#endif