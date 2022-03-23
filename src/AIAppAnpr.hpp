#ifndef AIAppAnpr_hpp
#define AIAppAnpr_hpp

#include "AIApplication.hpp"

class AIAppAnpr : public AIApplication
{
public:
    AIAppAnpr(Application* app);
    ~AIAppAnpr();

    virtual bool Initialize(int numThreads) override;
};


#endif