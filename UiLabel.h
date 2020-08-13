#ifndef UILABEL_H_INCLUDED
#define UILABEL_H_INCLUDED

#include <string>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include "UiComponent.h"
#include "Vector2i.h"

class UiLabel : public UiComponent
{
private:
    std::string label;
    TTF_Font* font;
    SDL_Texture* labelTexture;

public:
    UiLabel() = delete;
    UiLabel( int x, int y, int W, int H, std::string label, TTF_Font* font, SDL_Color color, UiCoordsSystem system = UiCoordsSystem::TopLeft );

    ~UiLabel();

    //Methods
    void Draw();
    void UpdateLabel( std::string newLabel );
    void UpdateColor( SDL_Color newColor );
};

#endif // UILABEL_H_INCLUDED
