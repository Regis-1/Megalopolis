#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED

#include <iostream>
#include <string>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

//Singleton class
class Logger
{
private:
    Logger() {};
    Logger(const Logger&) {};
    ~Logger() {}
public:
    static Logger& Get()
    {
        static Logger instance;
        return instance;
    }

    //Methods
    void PrintMessage(std::string msg); //Print custom message
    void PrintSdlError(); //Print SDL_GetError()
    void PrintSdlImageError(); //Print IMG_GetError()
    void PrintSdlTtfError(); //Print TTF_GetError()
};

#endif // LOGGER_H_INCLUDED
