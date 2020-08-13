#include "UiPanel.h"

UiPanel::UiPanel(int x, int y, int w, int h, int parent_w, int parent_h, SDL_Color color, UiCoordsSystem coordsSystem)
    : UiComponent(x, y, w, h, parent_w, parent_h, color, coordsSystem)
{
    Positioning();
}


void UiPanel::Draw()
{
    Renderer::Get().SetDrawColor( this->color.r, this->color.g, this->color.b, this->color.a );
    SDL_Rect drawRect = { this->x, this->y, this->w, this->h };
    SDL_RenderFillRect( Renderer::Get().GetRenderer(), &drawRect );
    Renderer::Get().SetDrawColor( 0x00, 0x00, 0x00, 0x00 );

    if( !(this->content.empty()) )
    {
        for( unsigned int i = 0; i < this->content.size(); i++ )
        {
            content[i].Draw();
        }
    }
}

void UiPanel::Move( Vector2i vec )
{
    this->x += vec[0];
    this->y += vec[1];
}

void UiPanel::UpdatePos( int x, int y )
{
    this->x = x;
    this->y = y;
}
