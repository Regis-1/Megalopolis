#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <vector>
#include <math.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "Logger.h"
#include "Renderer.h"
#include "ResourceLoader.h"
#include "Vector3i.h"
#include "Vector2i.h"
#include "Camera.h"

#define TILE_WIDTH 32
#define TILE_HEIGHT 32

//Class of game map with size and its numerical representation
class Map
{
private:
    int N = 0;
    std::vector<SDL_Texture*> textures;
    Vector3i** tileMap = nullptr;

    //Private methods
    void LoadTexture( const char* path ); //Loading texture and storing it in std::vector
    void UnloadTexture( const int n ); //Destroying texture and erasing it from std::vector
    Vector2i GetTilePos( int r, int c ); //Getting position of tile
    int& GetTileTex( int r, int c ); //Getting id of used texture by this coordinates

public:
    Map() = delete;
    Map( int N );
    Map( const char* path );
    ~Map();

    //Methods
    void Draw(Camera cam); //Drawing whole map
    void DrawSelectionRect( int y, int x );
    void ChangeTile( int r, int c, Vector3i newVec ); //Changing tile to given in newVec
    int GetN() { return this->N; }
    void Save( const char* path );
    void GenerateMap();

    //Overloading
    Vector3i* operator[]( unsigned int n );
};

#endif // MAP_H_INCLUDED
