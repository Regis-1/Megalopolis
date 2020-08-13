#ifndef UICOMPONENT_H_INCLUDED
#define UICOMPONENT_H_INCLUDED

#include "SDL2/SDL.h"

#include "Renderer.h"

enum UiCoordsSystem
{
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight
};

class UiComponent
{
public:
    int x, y;
    int w, h;
    int parent_w, parent_h;
    SDL_Color color;
    UiCoordsSystem coordsSystem;
    int rel_x, rel_y; //for later relative positioning UiComponent in another UiComponent

    UiComponent() = delete;
    UiComponent( SDL_Color color ) : color(color) {}
    UiComponent( int x, int y, int w, int h, int par_w, int par_h, SDL_Color color, UiCoordsSystem crdSys, int rel_x = 0, int rel_y = 0)
        : x(x), y(y), w(w), h(h), parent_w(par_w), parent_h(par_h), color(color), coordsSystem(crdSys), rel_x(rel_x), rel_y(rel_y) {}

    virtual ~UiComponent() = default;

    //Methods
    void Positioning();
    virtual void Draw() = 0;
};

#endif // UICOMPONENT_H_INCLUDED

