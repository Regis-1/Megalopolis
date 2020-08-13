#include "Logger.h"

#include <iostream>

void Logger::PrintMessage(std::string msg)
{
    std::cout << "Message: " << msg << std::endl;
}

void Logger::PrintSdlError()
{
    std::cout << "SDL2 Error: " << SDL_GetError() << std::endl;
}

void Logger::PrintSdlImageError()
{
    std::cout << "SDL Image Error: " << IMG_GetError() << std::endl;
}

void Logger::PrintSdlTtfError()
{
    std::cout << "SDL Ttf Error: " << TTF_GetError() << std::endl;
}
