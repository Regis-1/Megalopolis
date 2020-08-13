#ifndef UIPANEL_H_INCLUDED
#define UIPANEL_H_INCLUDED

#include <vector>

#include "UiComponent.h"
#include "Vector2i.h"

class UiPanel : public UiComponent
{
private:
    std::vector<UiComponent> content;
public:
    UiPanel(int x, int y, int w, int h, int parent_w, int parent_h, SDL_Color color, UiCoordsSystem coordsSystem = UiCoordsSystem::TopLeft);
    ~UiPanel() = default;

    //Methods
    void Draw();
    void Move(Vector2i vec);
    void UpdatePos( int x, int y );
};

#endif // UIPANEL_H_INCLUDED
