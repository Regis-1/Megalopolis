#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "Logger.h"
#include "EventHandler.h"
#include "ResourceLoader.h"
#include "Map.h"
#include "UI.h"
#include "CityInformation.h"
#include "Vector2i.h"

class Game
{
private:
    const double FRAME_RATE = 1.0/60.0; //Constant Frames Per Second (60 is enough)
    int w, h; //Window width and height
    SDL_Window* mainWindow = nullptr;
    Map* gameMap = nullptr;
    UI* ui = nullptr;

    bool continueGame = false;

public:
    Game() = delete;
    Game( SDL_Window* window, bool continueGame = false );
    ~Game();
    void Run(); //Starting game loop
};

#endif // GAME_H_INCLUDED
