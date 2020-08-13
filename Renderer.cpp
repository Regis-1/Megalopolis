#include "Renderer.h"

SDL_Renderer* Renderer::GetRenderer()
{
    return this->renderer;
}

bool Renderer::CreateRenderer( SDL_Window* window )
{
    this->renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    if( this->renderer == nullptr )
    {
        Logger::Get().PrintSdlError();
        return false;
    }
    SDL_SetRenderDrawColor( this->renderer, 0x00, 0x00, 0x00, 0xff );

    return true;
}

void Renderer::SetDrawColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_SetRenderDrawColor( this->renderer, r, g, b, a);
}

void Renderer::ClearAll()
{
    SDL_RenderClear( this->renderer );
    SDL_RenderPresent( this->renderer );
}

void Renderer::Clear()
{
    SDL_RenderClear( this->renderer );
}

void Renderer::Update()
{
    SDL_RenderPresent( this->renderer );
}
