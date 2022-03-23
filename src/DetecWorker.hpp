#ifndef DetecWorker_hpp
#define DetecWorker_hpp

#include "Worker.hpp"

class DetecWorker : public Worker
{
public:
    DetecWorker(AIApplication* owner);
    ~DetecWorker();

    virtual void runThread() override;
    virtual void threadFunc() override;
};

#endif