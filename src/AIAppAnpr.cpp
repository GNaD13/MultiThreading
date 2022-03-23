#include "AIAppAnpr.hpp"
#include "DetecWorker.hpp"
#include "RecognitionWorker.hpp"

AIAppAnpr::AIAppAnpr(Application* app)
    : AIApplication(app)
{

}

AIAppAnpr::~AIAppAnpr()
{

}

bool AIAppAnpr::Initialize(int numThreads)
{
    SetNumThreads(numThreads);
    DetecWorker* detector = new DetecWorker(this);
    for(int i = 0; i < GetNumThreads(); i++)
    {
        RecognitionWorker* recognition = new RecognitionWorker(this, i);
    }
    return true;
}