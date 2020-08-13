#ifndef EVENTHANDLER_H_INCLUDED
#define EVENTHANDLER_H_INCLUDED

#include "SDL2/SDL.h"

#include "Logger.h"

struct HandlingOutput
{
    bool quit = false;
    bool keyPressed = false;
    int keyCode = 0;
    int mouseMovement[3] = {0, 0, 0};
    bool mouseButtons[2] = {false, false};
};

class EventHandler //Singleton
{
private:
    EventHandler() {};
    EventHandler(const EventHandler&) {}
    ~EventHandler() {};
public:
    static EventHandler& Get()
    {
        static EventHandler instance;
        return instance;
    }

    //Methods
    void Handle(bool &quitFlag); //probably to delete later
    HandlingOutput Handle();
};

#endif // EVENTHANDLER_H_INCLUDED
