#include "EventHandler.h"

void EventHandler::Handle(bool &quitFlag)
{
    SDL_Event e;
    while( SDL_PollEvent(&e) != 0 )
    {
        if( e.type == SDL_QUIT ) //If pressed CLOSE button
            quitFlag = true;
    }
}

HandlingOutput EventHandler::Handle()
{
    SDL_Event e;
    HandlingOutput output;

    while( SDL_PollEvent(&e) != 0 )
    {
        if( e.type == SDL_QUIT ) //If pressed CLOSE button
            output.quit = true;

        /* KEYBOARD KEYS HANDLING */
        else if( e.type == SDL_KEYDOWN )
        {
            output.keyPressed = true;

            //ESCAPE was pressed
            if( e.key.keysym.sym == SDLK_ESCAPE && ((int) e.key.repeat) == 0 )
            {
                output.quit = true;
            }
            //Ending of SDL_KEYDOWN
            if( output.keyPressed )
            {
                output.keyCode = (int)e.key.keysym.sym;
            }
        }

        /* MOUSE HANDLING */
        else if( e.type == SDL_MOUSEMOTION )
        {
            output.mouseMovement[0] = e.motion.x/32;
            output.mouseMovement[1] = e.motion.y/32;
            output.mouseMovement[2] = 1;
        }
        //Pressing mouse button
        else if( e.type == SDL_MOUSEBUTTONDOWN )
        {
            if( e.button.button == SDL_BUTTON_LEFT )
                output.mouseButtons[0] = true;
            else if( e.button.button == SDL_BUTTON_RIGHT )
                output.mouseButtons[1] = true;
        }
    }

    return output;
}
