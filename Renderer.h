#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "Logger.h"

//Global renderer class (SINGLETON)
class Renderer
{
private:
    Renderer() {}
    Renderer(const Renderer&) {}
    ~Renderer()
    {
        SDL_DestroyRenderer( this->renderer );
        this->renderer = nullptr;
    };

    SDL_Renderer* renderer = nullptr;
public:
    static Renderer& Get()
    {
        static Renderer instance;
        return instance;
    }

    //Methods
    SDL_Renderer* GetRenderer();
    bool CreateRenderer( SDL_Window* window );
    void SetDrawColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a );
    void ClearAll();
    void Clear();
    void Update();
};

#endif // RENDERER_H_INCLUDED
