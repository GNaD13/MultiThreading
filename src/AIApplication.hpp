#ifndef AIApplication_hpp
#define AIApplication_hpp

#include <vector>
#include <mutex>
#include <functional>
#include <string>
#include "Define.hpp"


class Application;
class Worker;

class AIApplication
{
public:
    enum State
    {
        READY,
        DETECTION,
        RECOGNIZE
    };

    AIApplication(Application* app);
    ~AIApplication();

    virtual bool Initialize(int numThreads) = 0;
    virtual void Run();
    virtual void Shutdown();

    void SetData(const int data) { mData = data; }
    int GetData() const { return mData; }

    int GetNumThreads() const { return mNumThreads; }
    void SetNumThreads(int num) { mNumThreads = num; }

    State GetState() const { return mState; }
    void SetState(const State& state) { mState = state; }

    bool GetStatus() const { return mIsRunning; } 
    void SetStatus(bool running) { mIsRunning = running; }

    const EventCallbackFunc& GetEventCallbackFunc() const { return mCallbackFunc; }
    void SetEventCallbackFunc(const EventCallbackFunc& callback) { mCallbackFunc = callback; }

    void AddWorker(Worker* worker);
    void RemoveWorker(Worker* worker);

    Application* GetApplication() const { return mApp; }
private:
    int mData;
    int mNumThreads;
    State mState;

    bool mIsRunning;
    Application* mApp;

    std::vector<Worker*> mWorker;

    EventCallbackFunc mCallbackFunc;
public:
    std::vector<int> mDataEvent;
    std::mutex mMutex;
    bool IsDataEventEmpty() { return mDataEvent.empty(); }
public:
    static AIApplication* InitAiApplication(AIAppType& type, Application* app);
};

#endif
