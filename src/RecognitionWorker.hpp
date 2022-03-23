#ifndef RecognitionWorker_hpp
#define RecognitionWorker_hpp

#include "Worker.hpp"

class RecognitionWorker : public Worker
{
public:
    RecognitionWorker(AIApplication* owner, int threadNum);
    ~RecognitionWorker();

    virtual void runThread() override;
    virtual void threadFunc() override;
private:
    int mThreadNum;
};

#endif