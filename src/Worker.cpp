#include "Worker.hpp"
#include "AIApplication.hpp"

Worker::Worker(AIApplication* owner)
    : mOwner(owner)
    , mIsRunning(true)
{
    mOwner->AddWorker(this);
}

Worker::~Worker()
{
    mOwner->RemoveWorker(this);
}