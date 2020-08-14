#include "Game.h"

Game::Game( SDL_Window* window, bool continueGame )
    : mainWindow(window), continueGame(continueGame)
{
    SDL_GetWindowSize( window, &this->w, &this->h );
}

Game::~Game()
{
    this->mainWindow = nullptr;
    this->gameMap = nullptr;
    this->ui = nullptr;
}

void Game::Run()
{
    //Game mechanics objects
    if( this->continueGame ) //if user wants to continue the game just load the save
        this->gameMap = new Map( "test.save" );
    else //else create new map with size 64 x 64 tiles
        this->gameMap = new Map( 64 );

    Camera camera = Camera( 0, 0, this->w, this->h );
    this->ui = new UI( this->w, this->h );
    HandlingOutput hOutput;
    Vector2i movementDirection; //vector to pass direction in which camera should move
    Vector2i selectedBuilding;

    bool render = true;
    double lastTime = SDL_GetTicks();
    double presentTime = 0;
    double deltaTime = 0;

    //FPS counter
    double fpsDelta = 0;
    int framesRendered = 0;

    //Gameplay objects
    //City information (name, current population, current budget, fps [TEMPORARY])
    CityInfo mainInfo = { "San Francisco", 0, 1000000, 0 };
    bool selectionPanel = false;

    while( !(hOutput.quit) )
    {
        //EVENT HANDLING
        hOutput = EventHandler::Get().Handle();

        //mouse movement
        if( hOutput.mouseMovement[2] == (int)true )
            camera.UpdateCursorPos( hOutput.mouseMovement[0], hOutput.mouseMovement[1] );

        //keys & buttons pressed
        if( hOutput.mouseButtons[0] )
            //this->gameMap->ChangeTile(camera[4]+camera[0]/32, camera[5]+camera[1]/32, Vector3i(1, selectedBuilding[0], selectedBuilding[1]));
            selectionPanel = true;
        else if( hOutput.mouseButtons[1] )
            //this->gameMap->ChangeTile(camera[4]+camera[0]/32, camera[5]+camera[1]/32, Vector3i(0,0,0));
            selectionPanel = false;
        if( hOutput.keyCode == (int)SDLK_z )
            this->gameMap->Save( "test.save" );
        //Generating section [TEMPORARY]
        else if( hOutput.keyCode == (int)SDLK_n && !(this->continueGame))
            this->gameMap->GenerateMap();
        //camera movement keys
        else if( hOutput.keyCode == (int)SDLK_w )
            movementDirection = Vector2i(0, -1);
        else if( hOutput.keyCode == (int)SDLK_s )
            movementDirection = Vector2i(0, 1);
        else if( hOutput.keyCode == (int)SDLK_a )
            movementDirection = Vector2i(-1, 0);
        else if( hOutput.keyCode == (int)SDLK_d )
            movementDirection = Vector2i(1, 0);

        //TIME MANAGEMENT
        presentTime = SDL_GetTicks();
        deltaTime += (presentTime - lastTime)/1000;
        fpsDelta += (presentTime - lastTime)/1000; //for fps counter
        lastTime = presentTime;

        //moving camera and animation
        if( deltaTime > this->FRAME_RATE )
        {
            camera.Move( this->gameMap->GetN(), movementDirection );
            deltaTime = 0;
            render = true;
        }
        //FPS counter
        if( fpsDelta > 1.0f )
        {
            mainInfo.fps = framesRendered;
            framesRendered = 0;
            fpsDelta = 0;
        }

        //RENDERING
        if( render )
        {
            Renderer::Get().Clear();
            this->gameMap->Draw(camera);
            this->ui->DrawSelectionRect( camera[4], camera[5] );
            this->ui->DrawSelectPanel( selectionPanel, camera );
            this->ui->DrawGameUiLayer( mainInfo );

            Renderer::Get().Update();
            render = false;
            framesRendered++;
        }
    }

    delete this->gameMap;
    delete this->ui;
}

