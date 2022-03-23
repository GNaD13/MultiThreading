#include <iostream>
#include <unistd.h>
#include <string>
#include "Application.hpp"
#include "AIApplication.hpp"
#include "Define.hpp"

AIAppType type = AIAppType::AI_ITS;

void callback(std::string& str, int& data)
{
    // std::cout << data << std::endl;
}

int main()
{
    Application app;
    app.Begin();
    // Begin
    bool success = app.Initialize(BIND_EVENT_FN(callback), type, 100);
    if(success)
    {
        app.Run();
    }

    int i = 0;
    while(true)
    {
        if(i > 50) i = 0;
        app.SetData(i);
        i++;
        usleep(10);
    }
    // End
    app.End();
    return 0;
}