#include "Manager.h"

Manager::~Manager()
{
    SDL_DestroyWindow( this->mainWindow );
    this->mainWindow = nullptr;
}

//Initialization of SDL components. Returns true if some error occurred.
bool Manager::Init()
{
    if( SDL_Init(SDL_INIT_VIDEO) < 0 ) //SDL initialization
    {
        Logger::Get().PrintSdlError();
        return true;
    }
    else
        if( !(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) ) //SDL_image initialization
        {
            Logger::Get().PrintSdlImageError();
            return true;
        }
        else
            if( TTF_Init() == -1 ) //SDL_ttf initialization
            {
                Logger::Get().PrintSdlTtfError();
                return true;
            }
            else
                Logger::Get().PrintMessage("Initialization done.");

    return false;
}

void Manager::Close()
{
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

//Starting the SDL window and application. Function returns true if any error occurred.
bool Manager::Start(const char* title, int w, int h)
{
    mainWindow = SDL_CreateWindow( title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN );
    if( mainWindow == nullptr )
    {
        Logger::Get().PrintSdlError();
        return true;
    }
    else
    {
        if( !(Renderer::Get().CreateRenderer( mainWindow )) )
            return true;
        Logger::Get().PrintMessage("Renderer created.");
    }

    return false;
}

void Manager::MainMenu()
{
    Logger::Get().PrintMessage("Main menu started.");
    HandlingOutput hOutput;

    //Program's main loop
    while( !(hOutput.quit) )
    {
        hOutput = EventHandler::Get().Handle();

        //Main menu logic
        if( hOutput.keyCode == (int)SDLK_l )
        {
            if( !(this->gameIsRunning) )
            {
                this->game = new Game( mainWindow );
                this->gameIsRunning = true;
            }
        }
        if( hOutput.keyCode == (int)SDLK_k )
        {
            if( !(this->gameIsRunning) )
            {
                this->game = new Game( mainWindow, true );
                this->gameIsRunning = true;
            }
        }

        if( this->gameIsRunning )
        {
            Logger::Get().PrintMessage("Starting game...");
            game->Run();
            Renderer::Get().SetDrawColor(0x00, 0x00, 0x00, 0xff);
            delete this->game;
            this->gameIsRunning = false;
        }
        //Renderer drawing
        Renderer::Get().ClearAll();
    }
}
