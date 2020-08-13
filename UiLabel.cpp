#include "UiLabel.h"

UiLabel::UiLabel( int x, int y, int W, int H, std::string label, TTF_Font* font, SDL_Color color, UiCoordsSystem system )
    : UiComponent(x, y, 0, 0, W, H, color, system), label(label), font(font)
{
    SDL_Surface* t_Surface = TTF_RenderText_Solid( this->font, this->label.c_str(), this->color );
    this->labelTexture = SDL_CreateTextureFromSurface( Renderer::Get().GetRenderer(), t_Surface );
    if( this->labelTexture == nullptr )
        Logger::Get().PrintMessage("Cannot create labelTexture from surface!");
    this->w = t_Surface->w;
    this->h = t_Surface->h;
    this->rel_x = x;
    this->rel_y = y;

    SDL_FreeSurface( t_Surface ); //Deleting surface which we don't need anymore
    t_Surface = nullptr;

    Positioning();
}

UiLabel::~UiLabel()
{
    SDL_DestroyTexture( this->labelTexture );
    this->labelTexture = nullptr;
    this->font = nullptr;
}

void UiLabel::Draw()
{
    SDL_Rect srcRect = { 0, 0, this->w, this->h };
    SDL_Rect dstRect = { this->x, this->y, this->w, this->h };
    SDL_RenderCopy( Renderer::Get().GetRenderer(), this->labelTexture, &srcRect, &dstRect );
}

void UiLabel::UpdateLabel( std::string newLabel )
{
    this->label = newLabel;
    SDL_DestroyTexture( this->labelTexture );
    SDL_Surface* t_Surface = TTF_RenderText_Solid( this->font, this->label.c_str(), this->color );
    this->labelTexture = SDL_CreateTextureFromSurface( Renderer::Get().GetRenderer(), t_Surface );
    if( this->labelTexture == nullptr )
        Logger::Get().PrintMessage("Cannot create labelTexture from surface!");
    this->w = t_Surface->w;
    this->h = t_Surface->h;
    SDL_FreeSurface( t_Surface );
    t_Surface = nullptr;

    Positioning();
}

void UiLabel::UpdateColor( SDL_Color newColor )
{
    this->color = newColor;
}
