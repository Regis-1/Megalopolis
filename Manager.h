#ifndef MANAGER_H_INCLUDED
#define MANAGER_H_INCLUDED

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include "Logger.h"
#include "EventHandler.h"
#include "Game.h"

class Manager
{
private:
    SDL_Window* mainWindow = nullptr;

    Game* game = nullptr;
    bool gameIsRunning = false;

public:
    Manager() {}
    ~Manager();
    bool Init(); //Initializing SDL and its components
    void Close(); //Closing SDL and its components
    bool Start( const char* title, int w, int h );
    void MainMenu(); //Starting menu loop
};

#endif // MANAGER_H_INCLUDED
