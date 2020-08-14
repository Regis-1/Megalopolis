#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <vector>
#include <map>
#include <math.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "Logger.h"
#include "Renderer.h"
#include "ResourceLoader.h"
#include "Camera.h"
#include "Vector3i.h"

#define TILE_SIZE 32

enum Tile
{
    ground,
    water,
    forest,
    household_active,
    household_inactive,
    powerplant
};

//Class of game map with size and its numerical representation
class Map
{
private:
    int N;
    std::vector<SDL_Texture*> textures;
    //MAP for Id -> texture tile converstion [need to automate this]
    std::map<int, Vector3i> textureTiles = {
        {0, Vector3i(0,0,0)}, {1, Vector3i(0,1,0)},
        {2, Vector3i(0,0,1)}, {3, Vector3i(1,0,0)},
        {4, Vector3i(1,1,0)}, {5, Vector3i(1,2,0)}
    };
    int** idMap = nullptr;

    //Private methods
    void LoadTexture( const char* path ); //Loading texture and storing it in std::vector
    void UnloadTexture( const int n ); //Destroying texture and erasing it from std::vector

public:
    Map() = delete;
    Map( int N );
    Map( const char* path );
    ~Map();

    //Methods
    void Draw(Camera cam); //Drawing whole map
    void DrawSelectionRect( int y, int x );
    int GetN() { return this->N; }
    void Save( const char* path );
    void GenerateMap();

    //Overloading
    int* operator[]( unsigned int n );

};

#endif // MAP_H_INCLUDED
