#include "UI.h"

UI::UI( int w, int h )
    : w(w), h(h)
{
    this->mainFont = TTF_OpenFont("Res/Arial.ttf", 12);
    if( mainFont == nullptr )
        Logger::Get().PrintMessage("Unable to open main font!");

    this->ul_fpsCounter = new UiLabel( 0, 0, this->w, this->h, ".", this->mainFont, this->col_black, UiCoordsSystem::TopRight );
    this->ul_populationStatus = new UiLabel( 0, 0, this->w, this->h, ".", this->mainFont, this->col_black, UiCoordsSystem::BottomLeft );
    this->ul_budgetStatus = new UiLabel( 0, 0, this->w, this->h, ".", this->mainFont, this->col_black, UiCoordsSystem::BottomRight );
    this->up_testPanel = new UiPanel(0, 0, 96, 160, this->w, this->h, this->col_pastelBlue);
}

UI::~UI()
{
    TTF_CloseFont( this->mainFont );
    delete this->ul_fpsCounter;
    delete this->up_testPanel;
    this->mainFont = nullptr;
    this->ul_fpsCounter = nullptr;
    this->up_testPanel = nullptr;
}

void UI::DrawSelectionRect( int cursor_x, int cursor_y )
{
    SDL_Rect selectionRect = {cursor_x*32, cursor_y*32, 32, 32};

    Renderer::Get().SetDrawColor(0xff, 0x00, 0x00, 0xff);
    SDL_RenderDrawRect(Renderer::Get().GetRenderer(), &selectionRect);
    Renderer::Get().SetDrawColor(0x00, 0x00, 0x00, 0xff);
}

void UI::DrawSelectPanel( bool drawSelectPanel, Camera camera )
{
    if( drawSelectPanel )
    {
        if( !(camera.lastMoveVec == Vector2i(0,0)) )
            this->up_testPanel->Move(-camera.lastMoveVec * 32);
        this->up_testPanel->Draw();
    }
    else
    {
        this->up_testPanel->UpdatePos( (camera[4] + 1)*32, camera[5]*32 );
    }
}

void UI::DrawGameUiLayer( CityInfo info )
{
    this->ul_fpsCounter->UpdateLabel( std::to_string(info.fps) );
    this->ul_populationStatus->UpdateLabel( "Population: " + std::to_string(info.population) );
    this->ul_budgetStatus->UpdateLabel( "Budget: " + std::to_string(info.budget) );

    this->ul_fpsCounter->Draw();
    this->ul_populationStatus->Draw();
    this->ul_budgetStatus->Draw();
}
