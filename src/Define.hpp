#ifndef Define_hpp
#define Define_hpp

#include <functional>

using EventCallbackFunc = std::function<void(std::string&, int&)>;
#define BIND_EVENT_FN(x) std::bind(&x, std::placeholders::_1, std::placeholders::_2)

enum class AIAppType
{
    AI_FACEMASK_DETECTION = 0,
    AI_FACE_RECOGNITION = 1,
    AI_HUMAN_DETECTION = 2,
    AI_ITS = 3,
    AI_FIRE_DETECTION = 4,
    AI_SOCIAL_DISTANCING = 5
};

#endif