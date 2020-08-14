#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include "Renderer.h"
#include "Logger.h"
#include "CityInformation.h"
#include "Camera.h"

#include "UiLabel.h"
#include "UiPanel.h"

class UI
{
private:
    int w, h;
    TTF_Font* mainFont;

    SDL_Color col_black = {0x00, 0x00, 0x00};
    SDL_Color col_blue = {0x00, 0x00, 0xff};
    SDL_Color col_pastelBlue = {0x6b, 0xb5, 0xff};

    //TEMPORARY ui information for testing purposes
    UiLabel* ul_fpsCounter = nullptr;
    UiLabel* ul_populationStatus = nullptr;
    UiLabel* ul_budgetStatus = nullptr;
    UiPanel* up_testPanel = nullptr;

public:
    UI() = delete;
    UI( int w, int h );
    ~UI();

    void DrawSelectionRect( int cursor_x, int cursor_y ); //draws simple red square over tile where cursor is
    void DrawSelectPanel( bool drawSelectPanel, Camera camera ); //drawing panel with information about clicked entity
    void DrawGameUiLayer( CityInfo info ); //draws simple [FOR NOW] stats for players
};

#endif // UI_H_INCLUDED
