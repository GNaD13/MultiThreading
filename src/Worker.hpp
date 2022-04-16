#ifndef Worker_hpp
#define Worker_hpp

#include <thread>
#include <vector>
#include <chrono>

class AIApplication;

class Worker
{
public:
    Worker(AIApplication* owner);
    virtual ~Worker();
    
    virtual void runThread() = 0;
    virtual void threadFunc() = 0;
    void stop() { mIsRunning = false; }
    void join() { mThread.join(); }

    AIApplication* GetAIApplication() { return mOwner; }
protected:
    std::thread mThread;
    bool mIsRunning;
private:
    AIApplication* mOwner;
};

#endif
