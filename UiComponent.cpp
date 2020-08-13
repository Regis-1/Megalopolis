#include "UiComponent.h"

void UiComponent::Positioning()
{
    switch( this->coordsSystem )
    {
    case UiCoordsSystem::TopLeft:
        break;
    case UiCoordsSystem::TopRight:
        this->x = this->parent_w - this->w - this->rel_x;
        break;
    case UiCoordsSystem::BottomLeft:
        this->y = this->parent_h - this->h - this->rel_y;
        break;
    case UiCoordsSystem::BottomRight:
        this->x = this->parent_w - this->w - this->rel_x;
        this->y = this->parent_h - this->h - this->rel_y;
        break;
    }
}
